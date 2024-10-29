#pragma once
#include <memory>

class OWindow;

class OGame
{

public:
	OGame();
	~OGame();

	void run();
	void quit();

protected:

	bool m_isRunning = true;
	std::unique_ptr<OWindow> m_display; //con este puntero no hace falta llamarlo en el deconstructor para borrarlo
};

