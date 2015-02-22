/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_SoundManager_
#define _hrengin_SoundManager_

#include <hrengin/sound/sound.h>

namespace hrengin {
namespace sound {
class Sound;

//! This class is used to manage all audio output
class SoundManager {
public:
	virtual ~SoundManager ()
	{
	};

	virtual void addSound (char const* fileName) = 0;
	virtual void initSounds () = 0;
	virtual void playSound (char const* fileName) = 0;
};

//! Create new sound manager
HR_SND_EXP SoundManager* createSoundManager ();

} // namespace sound
} // namespace hrengin
#endif//_hrengin_SoundManager_
