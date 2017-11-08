#include "stdafx.h"

#include "PageState.h"

SelectState PageState::select = *new SelectState();
FlyWeightState PageState::flyWeight = *new FlyWeightState();
