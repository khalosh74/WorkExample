using System;
using System.Collections.Generic;

public class TypeHashSet<TBase> : HashSet<Type> where TBase : class
{
    public TypeHashSet() : base(new TypeEqualityComparer())
    {
    }
}
