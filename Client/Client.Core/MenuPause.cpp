#include "MenuPause.h"
#include "GraphicUtil.h"

MenuPause::MenuPause(GraphicUtil &utilities) : m_utilities(utilities)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("menuPause.layout");
	m_windows->getChild(1)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuPause::onContinueButtonClicked, this));
	m_windows->getChild(2)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuPause::onOptionButtonClicked, this));
	m_windows->getChild(3)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuPause::onQuitButtonClicked, this));
}

void MenuPause::display()
{
	m_systemd.getDefaultGUIContext().setRootWindow(m_windows);
}

void MenuPause::hide()
{
	m_systemd.getDefaultGUIContext().setRootWindow(0);
}

void MenuPause::checkPause()
{
	if (m_isEnable && m_utilities.getCEGUIEventReceiver().getKeyStateList()[irr::KEY_ESCAPE] == true)
	{
		m_utilities.setGuiCamera();
		this->display();
	}
}

bool MenuPause::onOptionButtonClicked()
{
	std::cout << "Not implemented" << std::endl;
	return (true);
}

bool MenuPause::onQuitButtonClicked()
{
	std::exit(0);
	return (true);
}

bool MenuPause::onContinueButtonClicked()
{
	std::cout << "Game resumed" << std::endl;
	m_utilities.setFPSCamera();
	this->hide();
	return (true);
}