using System;
using System.Collections.Generic;

public class TypeDictionary<TKeyBase, TValue> : Dictionary<Type, TValue> where TKeyBase : class
{
    public TypeDictionary() : base(new TypeEqualityComparer())
    {
    }
}