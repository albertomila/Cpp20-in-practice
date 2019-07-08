using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Comando
{
    class UITabPageCreator
    {
        public const int MAX_TABS = 11;
        private static int nextGeneratedTabIndex = 0;

        public static Gtk.Fixed GetCurrentCanvas(Gtk.Notebook parentNotebook)
        {
            Gtk.ScrolledWindow page = (Gtk.ScrolledWindow)parentNotebook.GetNthPage(parentNotebook.Page);
            Gtk.Viewport viewport = (Gtk.Viewport)page.Children[0];
            Gtk.Fixed canvas = (Gtk.Fixed)viewport.Children[0];
            return canvas;
        }

        public static UITabPage CreateUICanvasTab(Gtk.Notebook parentNotebook, GameConfigDB gameConfigDB, bool isInitializing = false)
        {
            Gtk.ScrolledWindow scrolledWindow = new Gtk.ScrolledWindow();
            scrolledWindow.Name = "_scrolledWindow" + nextGeneratedTabIndex;
            scrolledWindow.ShadowType = ((Gtk.ShadowType)(1));
            scrolledWindow.ShowAll();

            Gtk.Viewport viewport = new Gtk.Viewport();
            viewport.ShadowType = ((Gtk.ShadowType)(0));

            Gtk.Fixed canvas = new Gtk.Fixed();
            canvas.WidthRequest = 800;
            canvas.HeightRequest = 600;
            canvas.Name = "_gameCanvas" + nextGeneratedTabIndex;
            canvas.HasWindow = false;
            canvas.ShowAll();
            viewport.Add(canvas);
            viewport.ShowAll();
            scrolledWindow.Add(viewport);

            Gtk.Viewport viewportLabel = new Gtk.Viewport();
            viewportLabel.ShadowType = ((Gtk.ShadowType)(0));
            viewportLabel.WidthRequest = 80;
            viewportLabel.HeightRequest = 30;

            Gtk.Label label = new Gtk.Label();
            label.Name = "label1";
            label.LabelProp = global::Mono.Unix.Catalog.GetString(gameConfigDB.GetName());
            label.ShowAll();
            viewportLabel.Add(label);

            if (parentNotebook.NPages <= 0 || isInitializing)
            {
                parentNotebook.Add(scrolledWindow);
                parentNotebook.SetTabLabel(scrolledWindow, viewportLabel);
            }
            else
            {
                parentNotebook.InsertPage(scrolledWindow, viewportLabel, parentNotebook.NPages - 1);
                parentNotebook.Page = parentNotebook.NPages - 2;
            }

            UITabPage tabPage = new UITabPage(gameConfigDB, scrolledWindow, viewport, label, canvas);
			tabPage.InitDropEvent();
            scrolledWindow.Data.Add("UITabPage", tabPage);

            return tabPage;
        }

        public static void CreateUICanvasButtonAddTab(Gtk.Window window, Gtk.Notebook parentNotebook, Gtk.ButtonReleaseEventHandler buttonPressEvent)
        {
            Gtk.ScrolledWindow scrolledWindow = new Gtk.ScrolledWindow();
            scrolledWindow.Name = "_scrolledWindow" + nextGeneratedTabIndex;
            scrolledWindow.ShadowType = ((Gtk.ShadowType)(1));
            scrolledWindow.ShowAll();

            Gtk.Image buttonAddTabImage = new Gtk.Image();
			buttonAddTabImage.Pixbuf = global::Stetic.IconLoader.LoadIcon(window, "gtk-add", Gtk.IconSize.Button);
			buttonAddTabImage.ShowAll();

            Gtk.Button buttonAddTab = new Gtk.Button();
            buttonAddTab.CanFocus = true;
            buttonAddTab.Name = "_buttonAddhostEntry";
            buttonAddTab.Image = buttonAddTabImage;
            buttonAddTab.ShowAll();
			buttonAddTab.ButtonReleaseEvent += buttonPressEvent;

			Gtk.Viewport viewportLabel = new Gtk.Viewport();
			viewportLabel.ShadowType = ((Gtk.ShadowType)(0));
            viewportLabel.Add(buttonAddTab);

            parentNotebook.Add(scrolledWindow);
            parentNotebook.SetTabLabel(scrolledWindow, viewportLabel);
        }
    }
}
