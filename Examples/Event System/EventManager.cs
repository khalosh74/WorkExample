using System;
using UnityEngine;

//Note: EventManager is a class with the porpuse of managing EventEntities and Handlers by correctly mapping them
//and execute correct Handlers to the event being fired.
//this class implement Singelton Pattern.
public class EventManager : MonoBehaviour
{
    private static EventManager _instance;

    public static EventManager Instance { get { return _instance; } }

    private EventRegistry _eventRegistry;
    private HandlerRegistry _handlerRegistry;

    private BehaviorRegistry _behaviorRegistry;

    private void Awake()
    {
        Initialize();
    }
    private void Initialize()
    {
        if (Instance == null)
        {
            _instance = this;

            _eventRegistry = new ();
            _handlerRegistry = new ();
            _behaviorRegistry = new ();
        }
        else
        {
            Destroy(gameObject);
        }
    }

    public void RegisterBehavior<TEvent, THandler>(TEvent eventEntity = default, params THandler[] handlers)
where TEvent : IEventEntity
where THandler : IEventHandler<TEvent>
    {
        _eventRegistry.Add(typeof(TEvent));
        _handlerRegistry.Add(typeof(THandler));
        _behaviorRegistry.Add(typeof(TEvent), typeof(THandler));
    }

    public void TriggerEvent<TEvent>(TEvent eventEntity) where TEvent : IEventEntity, new()
    {
        foreach (var item in _behaviorRegistry)
        {
            if (item.Key == typeof(TEvent))
            {
                foreach (var handlerType in item.Value)
                {
                    var handler = Activator.CreateInstance(handlerType);
                    var method = handlerType.GetMethod("Handle");
                    method.Invoke(handler, new object[] { eventEntity });
                }
            }
        }
    }

}
