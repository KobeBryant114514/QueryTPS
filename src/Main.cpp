#include <LoggerAPI.h>
#include <EventAPI.h>
#include <DynamicCommandAPI.h>
#include "version.h"
#include "Global.h"

using namespace std;
extern Logger logger;

std::string Color(float input, int a, int b) {
    auto output = std::to_string(input);
	if (input < a && input > b){
		return "§6" + output;
	}
	if (input <= b){
		return "§c" + output;
	}
	else return "§a" + output;
}

void RegCommand() {
	Event::RegCmdEvent::subscribe([](const Event::RegCmdEvent) {
        using ParamType = DynamicCommand::ParameterType;
        auto command = DynamicCommand::createCommand("tps", "查询服务器TPS", CommandPermissionLevel::Any, { (CommandFlagValue)0x80 }, { (CommandFlagValue)1 });
        command->addOverload();
        command->setCallback([](DynamicCommand const& command, CommandOrigin const& origin, CommandOutput& output, std::unordered_map<std::string, DynamicCommand::Result>& results) {
            output.success("当前服务器MSPT " + Color(mspt, 50, 100) + "，§r相当于实时TPS " + Color(CurrentTPS, 15, 10) + "§r。\n服务器1分钟内平均TPS " + Color(AverageTPS, 15, 10));
        });
        DynamicCommand::setup(std::move(command));
		return true;
    });
}

void PluginInit() {
	ExportAPI();
    RegCommand();
	CaculateTPS();
	Avtps();
}
