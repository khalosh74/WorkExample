using System;
using System.Collections.Generic;

public class TypeEqualityComparer : IEqualityComparer<Type>
{
    public bool Equals(Type x, Type y)
    {
        return x == y;
    }

    public int GetHashCode(Type obj)
    {
        return obj.GetHashCode();
    }
}

