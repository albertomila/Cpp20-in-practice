using System;
using System.Drawing;
namespace Comando
{
    
    public class UIUtils
	{
        public const string BUTTON_FONT = "Arial 14";
        public const string SECTION_FONT = "Arial 22";
        public const string CONSOLE_FONT = "Lucida Console 13";
        
        public static void SetWidgetPosition(Gtk.Fixed fixedCanvas, Gtk.Widget widget, Point position)
		{
			Gtk.Fixed.FixedChild child = Utils.static_cast<Gtk.Fixed.FixedChild>(fixedCanvas[widget]);
			child.X = position.X;
			child.Y = position.Y;
		}

		public static Point GetWidgetPosition(Gtk.Fixed fixedCanvas, Gtk.Widget widget)
		{
			Gtk.Fixed.FixedChild child = Utils.static_cast<Gtk.Fixed.FixedChild>(fixedCanvas[widget]);
            return new Point(child.X, child.Y);
        }

        public static double Distance(Point p1, Point p2)
        {
            double distance = Math.Sqrt(Math.Pow(p1.X - p2.X, 2) + Math.Pow(p1.Y - p2.Y, 2));
            return distance;
        }
        
        public static void ShutDownWindow<T>(ref T window) where T : Gtk.Window
        {
            window.Hide();
			window.Destroy();
            window = null;
        }
        
        public static void ShutDownWindowSafe<T>(ref T window) where T : Gtk.Window
		{
			if (window != null)
			{
				ShutDownWindow<T>(ref window);
			}
        }
    }
}
