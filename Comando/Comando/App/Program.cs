using System;
using Gtk;

namespace Comando
{
	class MainClass
	{
		public static void Main(string[] args)
		{
			MainApp.CreateInstance();
            MainApp.GetInstance().Init();
			MainApp.GetInstance().Run();
		}
	}
}
