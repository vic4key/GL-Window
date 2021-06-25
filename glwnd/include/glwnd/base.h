#pragma once

/**
 * @file   base.h
 * @author Vic P.
 * @brief  GL Base
 */

#include "event.h"

namespace glwnd
{

class GLBase : public GLEvent
{
public:
	GLBase();
	virtual ~GLBase();
};

}; // glwnd