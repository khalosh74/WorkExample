
/*
* Author: Khaled Alraas
* Aiming System for Bellus Battle
*/

public class Aim : MonoBehaviour
{
    // Enum for different rotation types
    enum AngleRotations { FullAngleRotation, HalvAngleRotation, FixedAnglesRotation }
    [SerializeField] private AngleRotations rotations;
    [SerializeField] private AngleRotations rotationsOverride;
    private Vector3 direction;
    private Quaternion rotation;
    private float angle;
    private bool usingOverride = false;

    // Update for mouse-based aiming
    private void Update()
    {
        // ... (other conditions)
        if (!playerDetails.IsUsingController)
        {
            // Calculate mouse-based aim direction
            mousePos = Input.mousePosition;
            direction = mousePos - Camera.main.WorldToScreenPoint(transform.position);
            angle = Mathf.Atan2(direction.y, direction.x) * Mathf.Rad2Deg;
            transform.rotation = Quaternion.AngleAxis(angle, Vector3.forward);
        }
    }

    // Default joystick aiming
    public void DefaultJoystickInputToAngleCalculation(InputAction.CallbackContext context)
    {
        // ... (other conditions)
        Vector2 t = context.ReadValue<Vector2>();
        if (t.x == 0 && t.y == 0 || usingOverride) return;
        angle = Mathf.Atan2(t.y, t.x) * Mathf.Rad2Deg;
        ChooseAngleRotation(rotations);
    }

    // Override joystick aiming
    public void OverrideJoystickInputToAngleCalculation(InputAction.CallbackContext context)
    {
        // ... (other conditions)
        usingOverride = true;
        Vector2 t = context.ReadValue<Vector2>();
        angle = Mathf.Atan2(t.y, t.x) * Mathf.Rad2Deg;
        ChooseAngleRotation(rotationsOverride);
    }

    // Choose rotation type based on the configuration
    private void ChooseAngleRotation(AngleRotations type)
    {
        switch (type)
        {
            case AngleRotations.FullAngleRotation:
                FullAngleRotation();
                break;
            case AngleRotations.HalvAngleRotation:
                HalvAngleRotation();
                break;
            case AngleRotations.FixedAnglesRotation:
                FixedAnglesRotation(amountOfFixedAngles);
                break;
        }
    }

    // Rotation functions
    private void FullAngleRotation()
    {
        rotation = Quaternion.AngleAxis(angle, Vector3.forward);
    }

    private void HalvAngleRotation()
    {
        if (angle > 90) rotation = Quaternion.AngleAxis(90, Vector3.forward);
        else if (angle < -90) rotation = Quaternion.AngleAxis(-90, Vector3.forward);
        else rotation = Quaternion.AngleAxis(angle, Vector3.forward);
    }
    private void FixedAnglesRotation(float amount)
    {
        float x = FULLCIRCLE / amount;
        float y = x / 2;
        float z = HALFCIRCLE - y;
        if ((angle >= -HALFCIRCLE && angle < -z) || (angle >= z && angle < HALFCIRCLE))
        {
            rotation = Quaternion.AngleAxis(-180, Vector3.forward);
            return;
        }
        for (float i = -z; i < z; i += x)
        {
            if (angle >= i && angle < i + x)
            {
                rotation = Quaternion.AngleAxis(i + y, Vector3.forward);
            }
        }
    }
}
