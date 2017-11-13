#include "stdafx.h"

#include "PageState.h"
#include "Page.h"
#include "SelectState.h"
#include "FlyWeightState.h"
#include "ComponentState.h"

SelectState PageState::select = *new SelectState();
FlyWeightState PageState::flyWeight = *new FlyWeightState();
ComponentState PageState::component = *new ComponentState();
