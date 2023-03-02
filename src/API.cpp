#include <RemoteCallAPI.h>
#include "Global.h"

void ExportAPI() {
	RemoteCall::exportAs("QueryTPS", "GetCurrentTPS", []() -> unsigned short {
		return CurrentTPS;
	});
	RemoteCall::exportAs("QueryTPS", "GetAverageTPS", []() -> float {
		return AverageTPS;
	});
	RemoteCall::exportAs("QueryTPS", "GetMSPT", []() -> float {
		return mspt;
	});
}