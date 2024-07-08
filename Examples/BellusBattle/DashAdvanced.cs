using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using Unity.VisualScripting;
using UnityEngine.Events;
//using UnityEditor.Rendering.LookDev;
//using UnityEditor.SceneManagement;
using UnityEngine.UIElements;
#if UNITY_EDITOR
using UnityEditor;
#endif
/*
* Author Khaled Alraas
*/
public class DashAdvanced : MonoBehaviour
{
    [Header("Bools")]
    [SerializeField] private bool canDash = true;
    [SerializeField] private bool stopGravityWhileDashing = true;
    [SerializeField] private bool isInvincibileWhileDashing = true;
    [SerializeField] private bool canMoveWhileDashing = false;
    private bool isFacingRight;
    private bool isDashing;
    private bool onControlOverride;
    private bool onFullMode;
    [Header("E1")]
    [SerializeField] private float dashingDistace = 24f;
    [SerializeField] private float dashingDuration = 0.2f;
    [SerializeField] private BoxCollider bcollider; // here
    private CharacterController cc;
    [Header("E2")]
    [SerializeField] private float airDashingDistace = 24f;
    [SerializeField] private float airDashingDuration = 0.2f;
    [Header("E3")]
    [SerializeField] private float dashUpAngle = 90f;
    [SerializeField] private float dashUpAngleRange = 20;
    [SerializeField] private bool canDashDown = false;
    private bool currentCanDashDown;
    [SerializeField] private float dashDownAngle = -90f;
    [SerializeField] private float dashDownAngleRange = 20;
    [Header("E4")]
    [SerializeField] private float deadZoneAngle = -90;
    [SerializeField] private float deadZoneAngleRange = 90;
    [Header("Extra")]
    [SerializeField] private float dashingActivationCooldown = 1f;
    [SerializeField] private LayerMask collisionLayer;
    [SerializeField] private TrailRenderer tr;
    [SerializeField] private GameObject CharacterGlow;
    [Header("Sounds")]
    [SerializeField] private PlayerSoundManager playerSoundManager;
    private Vector3 direction;
    private Vector3 velocity;
    [SerializeField] private PlayerMovement movement;
    private PlayerHealth health;
    private float currentDashingDistace;
    private float currentDashingDuration;
    private float gravity;
    public UnityEvent dashEvent;
    private Vector3 mousePos;
    [SerializeField] private PlayerDetails playerDetails;

    public bool IsDashing
    {
        get => isDashing;
    }

    public float VerticalDashForce
    {
        get => velocity.y;
    }

    public float HorizontalDashForce
    {
        get => velocity.x;
    }

    enum DashType { E1_BasicDash, E2_TwoStateDash, E3_AdvancedDash, E4_FullDash }
    [SerializeField] private DashType dashType;


    // Default Dash method (dash only horizontaly)
    public void DashWithJoystick(InputAction.CallbackContext context)
    {
        if (enabled == false || GameManager.Instance.GameIsPaused == true || GameManager.Instance.AcceptPlayerInput == false || (!canDash && isDashing)) return;
        if (canDash && !isDashing)
        {
            CheckDashType();
        }
    }

    // Override Dash method (dash into the direction of the joystick input)
    public void CheckDashWithJoystickDirection(InputAction.CallbackContext context)
    {
        if (GameManager.Instance.GameIsPaused == true || GameManager.Instance.AcceptPlayerInput == false || (!canDash && isDashing)) return;
        Flip();
        direction = context.ReadValue<Vector2>().normalized;
    }

    //Seting up Dash at the Start of the game
    private void Start()
    {
        currentDashingDistace = dashingDistace;
        currentDashingDuration = dashingDuration;
        currentCanDashDown = canDashDown;
        movement = GetComponent<PlayerMovement>();
        health = GetComponent<PlayerHealth>();
        gravity = movement.DownwardForce;
        cc = GetComponent<CharacterController>();
    }

    //Updating Dash each frame
    private void Update()
    {
        if (GameManager.Instance.GameIsPaused == true || GameManager.Instance.AcceptPlayerInput == false) return;

        if (!playerDetails.IsUsingController)
        {
            mousePos = Input.mousePosition;
            direction = (mousePos - Camera.main.WorldToScreenPoint(transform.position)).normalized;
        }

        if (isDashing)
        {
            if (canMoveWhileDashing && !stopGravityWhileDashing) cc.Move(velocity * Time.deltaTime);
            else if (canMoveWhileDashing) cc.Move((velocity - new Vector3(0f, movement.Velocity.y, 0f)) * Time.deltaTime);
            else if (!stopGravityWhileDashing) cc.Move((velocity - new Vector3(movement.Velocity.x, 0f, 0f)) * Time.deltaTime);
            else cc.Move((velocity - (Vector3)movement.Velocity) * Time.deltaTime);
        }
    }

    //check the type of dash we want to use
    private void CheckDashType()
    {
        switch (dashType)
        {
            case DashType.E1_BasicDash:
                SetDirection();
                break;
            case DashType.E2_TwoStateDash:
                CheckIfGrounded();
                SetDirection();
                break;
            case DashType.E3_AdvancedDash:
                CheckIfGrounded();
                SetDirectionWithControlOverride();
                break;
            case DashType.E4_FullDash:
                onFullMode = true;
                CheckIfGrounded();
                SetDirectionWithControlOverride();
                break;
        }

    }

    //BasicDashAction is a horizantal dash. Dashes toword the direction th
    private IEnumerator BasicDashAction()
    {
        StartDashProtocol();
        velocity = new Vector3(direction.x * currentDashingDistace, 0f, 0f);

        yield return new WaitForSeconds(currentDashingDuration);
        EndDashProtocol();
        yield return new WaitForSeconds(dashingActivationCooldown);
        CharacterGlow.SetActive(false);
        canDash = true;
    }
    private void StartDashProtocol()
    {

        playerSoundManager.PlayerDashSound();
        CheckForCollision();
        canDash = false;
        dashEvent.Invoke();
        tr.emitting = true; //See variable TrailRenderer tr
        gameObject.GetComponent<AfterImg>().StartTrail();
        CharacterGlow.SetActive(true);
        if (stopGravityWhileDashing)
        {
            movement.DownwardForce = 0f;
        }
        if (isInvincibileWhileDashing)
        {
            //health.SetInvincible(true);
        }
        isDashing = true;
    }
    private void EndDashProtocol()
    {
        isDashing = false;
        tr.emitting = false; //See variable TrailRenderer tr
        currentDashingDistace = dashingDistace;
        currentDashingDuration = dashingDuration;
        currentCanDashDown = canDashDown;
        movement.DownwardForce = gravity;
        onControlOverride = false;
        //health.SetInvincible(false);
    }
    private void SetDirection()
    {
        if (isFacingRight)
        {
            direction = Vector2.right;
        }
        else
        {
            direction = Vector2.left;
        }
        StartCoroutine(BasicDashAction());
    }
    private void SetDirectionWithControlOverride()
    {
        float angle;
        angle = Mathf.Atan2(direction.y, direction.x) * Mathf.Rad2Deg; // -90 degrees
        if (direction.x != 0 && direction.y != 0)
        {
            onControlOverride = true;
            if (angle >= dashUpAngle - dashUpAngleRange && angle <= dashUpAngle + dashUpAngleRange)
            {
                direction = Vector3.up;
                StartCoroutine(UpDashAction());
                return;
            }
            else if (currentCanDashDown && angle >= dashDownAngle - dashDownAngleRange && angle <= dashDownAngle + dashDownAngleRange)
            {
                direction = Vector3.down;
                StartCoroutine(UpDashAction());
                return;
            }
            else if (onFullMode && (direction.y >= 0 || currentCanDashDown))
            {
                StartCoroutine(FullDashAction());
                return;
            }

        }
        SetDirection();
    }
    private IEnumerator UpDashAction()
    {
        StartDashProtocol();
        velocity = new Vector3(0f, direction.y * currentDashingDistace - movement.Velocity.y, 0f);
        yield return new WaitForSeconds(currentDashingDuration);
        EndDashProtocol();
        yield return new WaitForSeconds(dashingActivationCooldown);
        CharacterGlow.SetActive(false);
        canDash = true;
    }
    private IEnumerator FullDashAction()
    {
        StartDashProtocol();

        velocity = new Vector3(direction.x * currentDashingDistace, direction.y * currentDashingDistace, 0f);
        yield return new WaitForSeconds(currentDashingDuration);
        EndDashProtocol();
        yield return new WaitForSeconds(dashingActivationCooldown);
        CharacterGlow.SetActive(false);
        canDash = true;
    }
    private void CheckIfGrounded()
    {
        if (!movement.IsGrounded)
        {
            currentCanDashDown = true;
            currentDashingDistace = airDashingDistace;
            currentDashingDuration = airDashingDuration;
        }
    }
    private void Flip()
    {
        if (isFacingRight && movement.Velocity.x < 0f || !isFacingRight && movement.Velocity.x > 0f)
        {
            isFacingRight = !isFacingRight;
        }
    }
    private void CheckForCollision()
    {
        RaycastHit hit;
        if (Physics.Raycast(transform.position + new Vector3(0f, 0.5f, 0), direction, out hit, currentDashingDistace * currentDashingDuration + cc.center.x, collisionLayer)) //10 is a the number that make dash distance works correct 
        {
            if (onControlOverride)
            {
                currentDashingDistace = hit.distance / currentDashingDuration - cc.center.x / currentDashingDuration;
                currentDashingDistace = Mathf.Abs(currentDashingDistace);
            }
            else
            {
                currentDashingDistace = hit.distance / currentDashingDuration - Mathf.Abs(movement.Velocity.x) - cc.center.x / currentDashingDuration;
            }
        }
    }
    public bool GetISFacingRight()
    {
        return isFacingRight;
    }
}