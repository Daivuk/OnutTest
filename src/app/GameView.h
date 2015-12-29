#pragma once
#include "View.h"

class Emitter;
class GameView : public seed::View
{
public:

    GameView();
    virtual ~GameView();

	virtual void OnShow();
	virtual void OnHide();
	
private:

    seed::Sprite*       m_dude;
    seed::Emitter*      m_fireFX;


};