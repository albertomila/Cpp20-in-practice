using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class FileOperationResult
{
    private bool _success = false;
    private string _result = string.Empty;

    public FileOperationResult(bool success)
    {
        _success = success;
    }

    public FileOperationResult(bool success, string result)
    {
        _success = success;
        _result = result;
    }

    public bool IsSuccess()
    {
        return _success;
    }

    public string GetResult()
    {
        return _result;
    }
}