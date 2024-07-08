using System;
using System.Collections.Generic;

//Note: IEventEntity is an interface with the porpuse taging classes that are EventEntities
public interface IEventEntity
{
}

//Note: HandlerRegistry is a class with the porpuse of storing EventEntities
public class EventRegistry : TypeHashSet<IEventEntity>
{

}