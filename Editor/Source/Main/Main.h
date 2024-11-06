#pragma once

#include <Kryos/Core/Application.h>

class KryosEditor : public Kryos::Application
{
public:
	KryosEditor(Kryos::ApplicationInfo&& info);
	~KryosEditor() override = default;
};
