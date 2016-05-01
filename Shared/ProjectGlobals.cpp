#include "ProjectGlobals.h"

const std::string	ProjectGlobals::GAME_NAME	= "Malefice";

const std::size_t	ProjectGlobals::NORMAL_TEAM_SIZE	= 7;
const std::size_t	ProjectGlobals::NORMAL_TEAMS_NB		= 2;
const std::size_t	ProjectGlobals::PREDATOR_TEAM_SIZE	= 1;
const std::size_t	ProjectGlobals::PREDATOR_TEAMS_NB	= 1;
const std::size_t	ProjectGlobals::MAX_PLAYERS_NB		= (ProjectGlobals::NORMAL_TEAM_SIZE * ProjectGlobals::NORMAL_TEAMS_NB) + (ProjectGlobals::PREDATOR_TEAM_SIZE * ProjectGlobals::PREDATOR_TEAMS_NB);

const std::string	ProjectGlobals::GAME_CLIENT_VERSION	= "0.1";

const std::string	ProjectGlobals::GAME_SERVER_VERSION = "0.1";

const std::string	ProjectGlobals::GAME_SERVER_DEFAULT_SETTINGS_FILENAME	= "settings.xml";
const std::string	ProjectGlobals::GAME_SERVER_DEFAULT_NAME				= ProjectGlobals::GAME_NAME + " Server";
const std::string	ProjectGlobals::GAME_SERVER_DEFAULT_PASSWORD			= "";
const std::string	ProjectGlobals::GAME_SERVER_DEFAULT_ADDRESS				= "127.0.0.1";
const short			ProjectGlobals::GAME_SERVER_DEFAULT_PORT				= 2504;

const std::string	ProjectGlobals::GAME_CLIENT_CORE_LOG_FILEPATH		= "logs/Client.Core.log";
const std::string	ProjectGlobals::GAME_CLIENT_LAUNCHER_LOG_FILEPATH	= "logs/Client.Launcher.log";
const std::string	ProjectGlobals::GAME_SERVER_LOG_FILEPATH			= "logs/Server.Core.Log";