#include <LoggerAPI.h>
#include <EventAPI.h>
#include <RegCommandAPI.h>
#include <DynamicCommandAPI.h>
#include "version.h"
#include "Global.h"

using namespace std;
extern Logger logger;

std::string Color(float tps) {
    auto StrTPS = std::to_string(tps);
	if (tps < 15 && tps > 10){
		return "§6" + StrTPS;
	}
	if (tps <= 10){
		return "§c" + StrTPS;
	}
	return "§a" + StrTPS;
}

std::string ColorMSPT(float mspt) {
    auto Strmspt = std::to_string(mspt);
	if (mspt >= 50 && mspt <= 100){
		return "§6" + Strmspt;
	}
	if (mspt > 100){
		return "§c" + Strmspt;
	}
	return "§a" + Strmspt;
}

void RegCommand() {
	Event::RegCmdEvent::subscribe([](const Event::RegCmdEvent) {
        using ParamType = DynamicCommand::ParameterType;
        auto command = DynamicCommand::createCommand("tps", "查询服务器TPS", CommandPermissionLevel::Any, { (CommandFlagValue)0x80 }, { (CommandFlagValue)1 });
        command->addOverload();
        command->setCallback([](DynamicCommand const& command, CommandOrigin const& origin, CommandOutput& output, std::unordered_map<std::string, DynamicCommand::Result>& results) {
            output.success("当前服务器MSPT " + ColorMSPT(mspt) + "，§r相当于实时TPS " + Color(CurrentTPS) + "§r。\n服务器1分钟内平均TPS " + Color(AverageTPS));
        });
        DynamicCommand::setup(std::move(command));
		return true;
    });
}

void PluginInit(){
	ExportAPI();
    RegCommand();
	CaculateTPS();
	Avtps();
}