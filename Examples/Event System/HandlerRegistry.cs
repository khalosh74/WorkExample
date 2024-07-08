using System;
using System.Collections.Generic;

//Note: IEventHandlerBase is an interface with the porpuse taging classes that are Handlers,
//not design to handle any operation.
public interface IEventHandlerBase
{
}

//Note: IEventHandler<TEvent> is an interface with the porpuse of allowing for specifying what EventEntity to be handled,
//is design to handle any operation.
public interface IEventHandler<TEvent> : IEventHandlerBase where TEvent : IEventEntity
{
    void Handle(TEvent eventEntity);
}

//Note: HandlerRegistry is a class with the porpuse of storing Handlers
public class HandlerRegistry : TypeHashSet<IEventHandlerBase>
{
  
}
