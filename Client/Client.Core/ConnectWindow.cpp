#include "ConnectWindow.h"

ConnectWindow::ConnectWindow()
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("connectWindows.layout");
	try
	{
		m_frameWindows = dynamic_cast<CEGUI::FrameWindow *>(m_windows);
		if (m_windows == nullptr)
			std::cout << "" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Failure while loading Frame windows:" << std::endl << std::endl;
		std::cout << e.what() << std::endl;
	}
	m_frameWindows->getCloseButton()->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ConnectWindow::onCloseButtonClicked, this));

}

void ConnectWindow::display()
{
	if (m_systemd.getDefaultGUIContext().getRootWindow() == nullptr)
	{
		std::cout << "Root Windows not found setting loading windows as root..." << std::endl;
		m_systemd.getDefaultGUIContext().setRootWindow(m_windows);
	}
	else
		m_systemd.getDefaultGUIContext().getRootWindow()->addChild(m_windows);
}

void ConnectWindow::hide()
{
	try {
		m_systemd.getDefaultGUIContext().getRootWindow()->getChild(66);
		m_systemd.getDefaultGUIContext().getRootWindow()->removeChild(66);
	}
	catch (std::exception &e) {
		std::cout << "Root windows not found. hiding loading windows as Root Windows" << std::endl;
		m_systemd.getDefaultGUIContext().setRootWindow(0);
	}
}

bool ConnectWindow::onCloseButtonClicked(const CEGUI::EventArgs& e)
{
	this->hide();
	return (true);
}