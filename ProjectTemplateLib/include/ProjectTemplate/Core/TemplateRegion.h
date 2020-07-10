#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>

#include <GameBackbone/Core/GameRegion.h>


namespace PT
{
    class libProjectTemplate TemplateRegion : public GB::GameRegion
    {
    public:
        using GB::GameRegion::GameRegion;
    };
}