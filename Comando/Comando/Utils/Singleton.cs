
public class Singleton<T> where T : class, new()
{
    private static T _instance = null;

    public static void CreateInstance()
    {
        _instance = new T();
    }

    public static void DestroyInstance()
    {
        _instance = null;
    }

    public static T GetInstance()
    {
        return _instance;
    }

    public static bool IsValid()
    {
        return _instance != null;
    }
}

