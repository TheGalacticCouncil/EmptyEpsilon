#include <i18n.h>
#include "shieldFreqencySelect.h"
#include "playerInfo.h"
#include "spaceObjects/playerSpaceship.h"

#include "screenComponents/shieldsEnableButton.h"

#include "gui/gui2_keyvaluedisplay.h"
#include "gui/gui2_selector.h"
#include "gui/gui2_progressbar.h"

GuiShieldFrequencySelect::GuiShieldFrequencySelect(GuiContainer* owner, string id)
: GuiElement(owner, id)
{
    (new GuiShieldsEnableButton(this, "SHIELDS_ENABLE"))->setPosition(0, 0, sp::Alignment::TopLeft)->setSize(GuiElement::GuiSizeMax, 50);
    GuiElement* calibration_row = new GuiElement(this, "");
    calibration_row->setPosition(0, 50, sp::Alignment::TopLeft)->setSize(GuiElement::GuiSizeMax, 50)->setAttribute("layout", "horizontalright");

    new_frequency = new GuiSelector(calibration_row, "", [this](int selected_shield_frequency, string value) {
        if (my_spaceship) {
            my_spaceship->selected_shield_frequency = selected_shield_frequency;
        }
    });
    new_frequency->setSize(120, 50);

    calibrate_button = new GuiButton(calibration_row, "", tr("shields","Calibrate"), [this]() {
        if (my_spaceship)
            my_spaceship->commandSetShieldFrequency(new_frequency->getSelectionIndex());
    });
    calibrate_button->setSize(GuiElement::GuiSizeMax, 50);
    
    for(int n=0; n<=SpaceShip::max_frequency; n++)
    {
        new_frequency->addEntry(frequencyToString(n), string(n));
    }
    new_frequency->setSelectionIndex(my_spaceship->selected_shield_frequency);
}

void GuiShieldFrequencySelect::onDraw(sp::RenderTarget& renderer)
{
    if (my_spaceship)
    {
        calibrate_button->setEnable(my_spaceship->shield_calibration_delay <= 0.0f);
        new_frequency->setEnable(my_spaceship->shield_calibration_delay <= 0.0f);
        new_frequency->setSelectionIndex(my_spaceship->selected_shield_frequency);
    }
    GuiElement::onDraw(renderer);
}

void GuiShieldFrequencySelect::onUpdate()
{
    if (my_spaceship && isVisible())
    {
        if (keys.weapons_shield_calibration_increase.getDown())
        {
            if (new_frequency->getSelectionIndex() >= new_frequency->entryCount() - 1)
            {
                new_frequency->setSelectionIndex(0);
            }
            else
            {
                new_frequency->setSelectionIndex(new_frequency->getSelectionIndex() + 1);
            }
        }

        if (keys.weapons_shield_calibration_decrease.getDown())
        {
            if (new_frequency->getSelectionIndex() <= 0)
            {
                new_frequency->setSelectionIndex(new_frequency->entryCount() - 1);
            }
            else
            {
                new_frequency->setSelectionIndex(new_frequency->getSelectionIndex() - 1);
            }
        }

        if (keys.weapons_shield_calibration_start.getDown())
        {
            my_spaceship->commandSetShieldFrequency(new_frequency->getSelectionIndex());
        }
    }
}
