/*
 Minetest-c55
 Copyright (C) 2010-11 celeron55, Perttu Ahola <celeron55@gmail.com>
 Copyright (C) 2011 Ciaran Gultnieks <ciaran@ciarang.com>
 Copyright (C) 2011 teddydestodes <derkomtur@schattengang.net>

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along
 with this program; if not, write to the Free Software Foundation, Inc.,
 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "guiSettingsMenu.h"
#include "debug.h"
#include "serialization.h"
#include "main.h"
#include <string>
#include <IGUICheckBox.h>
#include <IGUIEditBox.h>
#include <IGUIButton.h>
#include <IGUIStaticText.h>
#include <IGUIListBox.h>
#include <IGUIFont.h>
#include "settings.h"

GUISettingsMenu::GUISettingsMenu(gui::IGUIEnvironment* env,
		gui::IGUIElement* parent, s32 id, IMenuManager *menumgr, MainMenuData * data) :
	GUIModalMenu(env, parent, id, menumgr)
{
	m_data = data;
}

GUISettingsMenu::~GUISettingsMenu()
{
	removeChildren();
}

void GUISettingsMenu::removeChildren()
{
	const core::list<gui::IGUIElement*> &children = getChildren();
	core::list<gui::IGUIElement*> children_copy;
	for (core::list<gui::IGUIElement*>::ConstIterator i = children.begin(); i
			!= children.end(); i++)
	{
		children_copy.push_back(*i);
	}
	for (core::list<gui::IGUIElement*>::Iterator i = children_copy.begin(); i
			!= children_copy.end(); i++)
	{
		(*i)->remove();
	}
}

void GUISettingsMenu::regenerateGui(v2u32 screensize)
{
	/*
	 Remove stuff
	 */
	removeChildren();

	/*
	 Calculate new sizes and positions
	 */

	v2s32 size(620, 430);

	core::rect < s32 > rect(screensize.X / 2 - size.X / 2,
			screensize.Y / 2 - size.Y / 2, screensize.X / 2 + size.X / 2,
			screensize.Y / 2 + size.Y / 2);

	DesiredRect = rect;
	recalculateAbsolutePosition(false);

	v2s32 topleft(0, 0);
	changeCtype("");
	{
		core::rect < s32 > rect(0, 0, 125, 20);
		rect += topleft + v2s32(25, 10);
		//gui::IGUIStaticText *t =
		Environment->addStaticText(wgettext("SETTINGS"),
				rect, false, true, this, -1);
		//t->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_UPPERLEFT);
	}
	{
		core::rect < s32 > rect(0, 0, 125, 20);
		rect += topleft + v2s32(50, 50);
		//gui::IGUIStaticText *t =
		Environment->addStaticText(wgettext("GRAPHIC"),
				rect, false, true, this, -1);
		//t->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_UPPERLEFT);
	}
	{
		core::rect < s32 > rect(0, 0, 125, 20);
		rect += topleft + v2s32(400, 50);
		//gui::IGUIStaticText *t =
		Environment->addStaticText(wgettext("SOUND"),
				rect, false, true, this, -1);
		//t->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_UPPERLEFT);
	}
	{
		core::rect < s32 > rect(0, 0, 250, 20);
		rect += topleft + v2s32(370, 130);
		//gui::IGUIStaticText *t =
		Environment->addStaticText(wgettext("No Sound yet )-:"),
				rect, false, true, this, -1);
		//t->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_UPPERLEFT);
	}
	{
		core::rect < s32 > rect(0, 0, 600, 20);
		rect += topleft + v2s32(25, 390);
		//gui::IGUIStaticText *t =
		Environment->addStaticText(wgettext("Some settings only works after a restart of Minetest!"),
				rect, false, true, this, -1);
		//t->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_UPPERLEFT);
	}
	
	{
		core::rect<s32> rect(0, 0, 250, 30);
		rect += topleft + v2s32(50, 80);
		Environment->addCheckBox(m_data->fancy_trees, rect, this, GUI_ID_FANCYTREE_CB,
			wgettext("Fancy trees")); 
	}
	{
		core::rect<s32> rect(0, 0, 250, 30);
		rect += topleft + v2s32(50, 100);
		Environment->addCheckBox(m_data->smooth_lighting, rect, this, GUI_ID_SMOOTH_LIGHTING_CB,
				wgettext("Smooth Lighting"));
	}
	{
		core::rect<s32> rect(0, 0, 250, 30);
		rect += topleft + v2s32(50, 120);
		Environment->addCheckBox(m_data->clouds_3d, rect, this, GUI_ID_3D_CLOUDS_CB,
				wgettext("3D Clouds"));
	}
	{
		core::rect<s32> rect(0, 0, 250, 30);
		rect += topleft + v2s32(50, 140);
		Environment->addCheckBox(m_data->opaque_water, rect, this, GUI_ID_OPAQUE_WATER_CB,
				wgettext("Opaque water"));
	}
	{
		core::rect<s32> rect(0, 0, 250, 30);
		rect += topleft + v2s32(50, 170);
		Environment->addCheckBox(m_data->antialiasing, rect, this, GUI_ID_ANTIALIASING_CB,
				wgettext("Antialiasing"));
	}
	{
		core::rect<s32> rect(0, 0, 250, 30);
		rect += topleft + v2s32(50, 190);
		Environment->addCheckBox(m_data->fullscreen, rect, this, GUI_ID_FULLSCREEN_CB,
				wgettext("Fullscreen"));
	}
	{
		core::rect<s32> rect(0, 0, 250, 30);
		rect += topleft + v2s32(50, 210);
		Environment->addCheckBox(m_data->vsync, rect, this, GUI_ID_VSYNC_CB,
				wgettext("Vertical Synchronization"));
	}
	
	{
		core::rect < s32 > rect(0, 0, 600, 20);
		rect += topleft + v2s32(50, 260);
		//gui::IGUIStaticText *t =
		Environment->addStaticText(wgettext("Window size"),
				rect, false, true, this, -1);
		//t->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_UPPERLEFT);
	}
	// A listbox for the window size
	{
		core::rect<s32> rect(0, 30, 200, 100);
		//rect += topleft_server + v2s32(size_server.X-40-130, 100+25);
		rect += topleft + v2s32(50, 250);
		window_size_list = Environment->addListBox(rect, this, -1, true);
		item_ids[0] = window_size_list->addItem(L"640 x 480");
		item_ids[1] = window_size_list->addItem(L"800 x 600");
		item_ids[2] = window_size_list->addItem(L"1024 x 768");
		item_ids[3] = window_size_list->addItem(L"1200 x 900");
		item_ids[4] = window_size_list->addItem(L"1280 x 1024");
		item_ids[5] = window_size_list->addItem(L"1400 x 1050");
		item_ids[6] = window_size_list->addItem(L"1600 x 1200");
		item_ids[7] = window_size_list->addItem(L"1920 x 1080");
	}
	
	{
		core::rect < s32 > rect(0, 0, 100, 30);
		rect += topleft + v2s32(size.X - 100 - 20, size.Y - 40);
		Environment->addButton(rect, this, GUI_ID_BACK_BUTTON,
		wgettext("Save"));
	}
	{
		core::rect < s32 > rect(0, 0, 100, 30);
		rect += topleft + v2s32(size.X - 100 - 20 - 100 - 20, size.Y - 40);
		Environment->addButton(rect, this, GUI_ID_ABORT_BUTTON,
		wgettext("Cancel"));
	}

	changeCtype("C");
}

void GUISettingsMenu::drawMenu()
{
	gui::IGUISkin* skin = Environment->getSkin();
	if (!skin)
		return;
	video::IVideoDriver* driver = Environment->getVideoDriver();

	video::SColor bgcolor(50, 0, 0, 0);

	{
		core::rect < s32 > rect(0, 0, 620, 620);
		rect += AbsoluteRect.UpperLeftCorner;
		driver->draw2DRectangle(bgcolor, rect, &AbsoluteClippingRect);
	}

	gui::IGUIElement::draw();
}

bool GUISettingsMenu::acceptInput()
{
	{
		gui::IGUIElement *e = getElementFromId(GUI_ID_FANCYTREE_CB);
		if(e != NULL && e->getType() == gui::EGUIET_CHECK_BOX)
			m_data->fancy_trees = ((gui::IGUICheckBox*)e)->isChecked();
	}
	{
		gui::IGUIElement *e = getElementFromId(GUI_ID_SMOOTH_LIGHTING_CB);
		if(e != NULL && e->getType() == gui::EGUIET_CHECK_BOX)
			m_data->smooth_lighting = ((gui::IGUICheckBox*)e)->isChecked();
	}
	{
		gui::IGUIElement *e = getElementFromId(GUI_ID_3D_CLOUDS_CB);
		if(e != NULL && e->getType() == gui::EGUIET_CHECK_BOX)
			m_data->clouds_3d = ((gui::IGUICheckBox*)e)->isChecked();
	}
	{
		gui::IGUIElement *e = getElementFromId(GUI_ID_OPAQUE_WATER_CB);
		if(e != NULL && e->getType() == gui::EGUIET_CHECK_BOX)
			m_data->opaque_water = ((gui::IGUICheckBox*)e)->isChecked();
	}
	{
		gui::IGUIElement *e = getElementFromId(GUI_ID_ANTIALIASING_CB);
		if(e != NULL && e->getType() == gui::EGUIET_CHECK_BOX)
			m_data->antialiasing = ((gui::IGUICheckBox*)e)->isChecked();
	}
	{
		gui::IGUIElement *e = getElementFromId(GUI_ID_FULLSCREEN_CB);
		if(e != NULL && e->getType() == gui::EGUIET_CHECK_BOX)
			m_data->fullscreen = ((gui::IGUICheckBox*)e)->isChecked();
	}
	{
		gui::IGUIElement *e = getElementFromId(GUI_ID_VSYNC_CB);
		if(e != NULL && e->getType() == gui::EGUIET_CHECK_BOX)
			m_data->vsync = ((gui::IGUICheckBox*)e)->isChecked();
	}
	
	s32 selected_item = window_size_list->getSelected();
	if (selected_item != -1) { // if is something selected
		if (selected_item == item_ids[0]) {
			g_settings->set("screenW", "640");
			g_settings->set("screenH", "480");
		}
		if (selected_item == item_ids[1]) {
			g_settings->set("screenW", "800");
			g_settings->set("screenH", "600");
		}
		if (selected_item == item_ids[2]) {
			g_settings->set("screenW", "1024");
			g_settings->set("screenH", "768");
		}
		if (selected_item == item_ids[3]) {
			g_settings->set("screenW", "1200");
			g_settings->set("screenH", "900");
		}
		if (selected_item == item_ids[4]) {
			g_settings->set("screenW", "1280");
			g_settings->set("screenH", "1024");
		}
		if (selected_item == item_ids[5]) {
			g_settings->set("screenW", "1400");
			g_settings->set("screenH", "1050");
		}
		if (selected_item == item_ids[6]) {
			g_settings->set("screenW", "1600");
			g_settings->set("screenH", "1200");
		}
		if (selected_item == item_ids[7]) {
			g_settings->set("screenW", "1920");
			g_settings->set("screenH", "1080");
		}
	}
	
	g_settings->set("new_style_leaves", itos(m_data->fancy_trees));
	g_settings->set("smooth_lighting", itos(m_data->smooth_lighting));
	g_settings->set("enable_3d_clouds", itos(m_data->clouds_3d));
	g_settings->set("opaque_water", itos(m_data->opaque_water));
	g_settings->set("antialiasing", itos(m_data->antialiasing));
	g_settings->set("fullscreen", itos(m_data->fullscreen));
	g_settings->set("vsync", itos(m_data->vsync));
	
	return true;
}

bool GUISettingsMenu::resetMenu()
{
	return true;
}
bool GUISettingsMenu::OnEvent(const SEvent& event)
{
	if(event.EventType==EET_KEY_INPUT_EVENT)
	{
		if(event.KeyInput.Key==KEY_ESCAPE && event.KeyInput.PressedDown)
		{
			quitMenu();
			return true;
		}
	}
	if (event.EventType == EET_GUI_EVENT)
	{
		if (event.GUIEvent.EventType == gui::EGET_ELEMENT_FOCUS_LOST
				&& isVisible())
		{
			if (!canTakeFocus(event.GUIEvent.Element))
			{
				dstream << "GUIMainMenu: Not allowing focus change."
						<< std::endl;
				// Returning true disables focus change
				return true;
			}
		}
		if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED)
		{
			if(event.GUIEvent.Caller->getID() != GUI_ID_BACK_BUTTON &&
				event.GUIEvent.Caller->getID() != GUI_ID_ABORT_BUTTON)
			{
				changeCtype("");
			}

			switch (event.GUIEvent.Caller->getID())
			{
			case GUI_ID_BACK_BUTTON: //back
				acceptInput();
				quitMenu();
				return true;
			case GUI_ID_ABORT_BUTTON: //abort
				quitMenu();
				return true;
			}
			//Buttons
			changeCtype("C");

		}
	}
	return Parent ? Parent->OnEvent(event) : false;
}

