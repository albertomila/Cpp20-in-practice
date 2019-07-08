using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web;

class Utils
{
    public static T static_cast<T>(object value)
    {
        Debug.Assert(value != null, "Trying to cast invalid object!");

        if (typeof(T).IsEnum)
        {
            if (Enum.IsDefined(typeof(T), value))
            {
                T objectCasted = (T)(value);
                return objectCasted;
            }
        }
        else
        {
            T objectCasted = (T)Convert.ChangeType(value, typeof(T));
            if (objectCasted != null)
            {
                return objectCasted;
            }
        }

        Debug.Assert(false, "Cast failed!");
        return default(T);
    }

    public static T dynamic_cast<T>(object value) where T : class
    {
        Debug.Assert(value != null, "Trying to cast invalid object!");

        T objectCasted = value as T;
        if (objectCasted != null)
        {
            return objectCasted;
        }

        Debug.Assert(false, "Cast failed!");
        return default(T);
    }

	public static string EncodeHTML(string value)
	{
		string encoded = HttpUtility.HtmlEncode(value);
		return encoded;
	}

	public static string DecodeHTML(string value)
	{
		string decoded = HttpUtility.HtmlDecode(value);
		return decoded;
	}
}