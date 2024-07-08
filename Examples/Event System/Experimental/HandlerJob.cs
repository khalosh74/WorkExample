using Unity.Jobs;
using UnityEngine;

//Note: This class is an example on how to execute the operation multithreaded using Unity's Job System
public struct HandlerJob<TEvent> : IJob where TEvent : struct, IEventEntity
{
    public TEvent EventData;

    public void Execute()
    {
        // Your handler logic here
        Debug.Log($"Handled event of type {typeof(TEvent).Name}");
    }
}
