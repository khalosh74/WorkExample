using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//Example usage of the Event System
public class UnitTest : MonoBehaviour
{

    private void Start()
    {
        EventManager.Instance.RegisterBehavior<OrderPlacedEvent, SendEmailHandler>();
        EventManager.Instance.TriggerEvent(new OrderPlacedEvent());
    }
}


public class OrderPlacedEvent : IEventEntity { }
public class SpaceEvent : IEventEntity {
    public int value = 5;
}

public class SendEmailHandler : IEventHandler<OrderPlacedEvent>
{
    public void Handle(OrderPlacedEvent eventEntity)
    {
        Debug.Log(eventEntity);
    }
}

public class SayHiHandler : IEventHandler<SpaceEvent>
{
    public void Handle(SpaceEvent eventEntity)
    {
        Debug.Log("hi from " + eventEntity.value);
    }
}