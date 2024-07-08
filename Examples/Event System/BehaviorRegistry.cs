using System;

//Note: BehaviorRegistry is a class with the porpuse of mapping EventEntities to their corisponding list of Handlers.
public class BehaviorRegistry : TypeDictionary<Type, HandlerRegistry>
{
    public void Add(Type eventType, Type handlerType)
    {
        if (!this.ContainsKey(eventType))
        {
            this[eventType] = new HandlerRegistry();
        }
        this[eventType].Add(handlerType);
    }
}
