#ifndef BEAM_FREQUENCY_SELECTOR_H
#define BEAM_FREQUENCY_SELECTOR_H

#include "gui/gui2_selector.h"

class GuiBeamFrequencySelector : public GuiSelector
{
public:
    GuiBeamFrequencySelector(GuiContainer* owner, string id);

    virtual void onDraw(sp::RenderTarget& window);
    virtual void onUpdate() override;
};

#endif//BEAM_FREQUENCY_SELECTOR_H
