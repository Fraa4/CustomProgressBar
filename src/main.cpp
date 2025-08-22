#include <Geode/modify/PlayLayer.hpp>
#include <Geode/loader/Mod.hpp>
using namespace geode::prelude;


class $modify(PlayLayer) {
    struct Fields {
        bool movedProgressBar = false;
        bool pbSetting=false, pgSetting=false;
        int frameFound = 0;
        int percentageXPos = 394.5;
    };
    
    void updateProgressbar()
    {
        PlayLayer::updateProgressbar();
        
        //Check if progressBar and percentageLabel settings are changed and save new values
        bool pbNewSetting = GameManager::get()->m_showProgressBar;
        bool pbChanged = (pbNewSetting == m_fields->pbSetting);
        bool pgNewSetting = GameManager::get()->getGameVariable("0040");
        bool pgChanged = (pgNewSetting == m_fields->pgSetting);
        m_fields->pbSetting=pbNewSetting;
        m_fields->pgSetting=pgNewSetting;

        //run the function if any settings has changed
        bool runFunc=pbChanged || pgChanged;

        if(!m_fields->movedProgressBar || runFunc)
        {
            moveProgressBar();
            m_fields->movedProgressBar=true;
            log::info("moved progress bar");
        }
    };
    
    void moveProgressBar()
    {
        auto winSize = CCDirector::get()->getWinSize();
        
        auto vert = Mod::get()->getSettingValue<bool>("vertical-progress-bar");
        auto pos = Mod::get()->getSettingValue<std::string>("Position");
        auto scale = Mod::get()->getSettingValue<float>("Scale");

        bool pbSetting=m_fields->pbSetting;

        geode::log::info("{}",pos);
        m_progressBar->setScale(scale);
        m_percentageLabel->setScale(scale*0.5);

        if(vert)
        {
            if(pbSetting)
            {
                m_progressBar->setRotation(-90);
                m_progressBar-> setPositionY(winSize.height/2);
                m_percentageLabel->setPositionY(winSize.height/2+120*scale);
            }
            else
            {
                m_percentageLabel->setPositionY(winSize.height/2);
            }
            if(pos=="Right")
            {
                m_percentageLabel->setAnchorPoint(CCPoint(1, 0.5));
                m_percentageLabel->setPositionX(winSize.width);
                m_fields->percentageXPos = winSize.width;
                m_progressBar->setPositionX(winSize.width-10 * scale);
            }
            else
            {
                m_percentageLabel->setAnchorPoint(CCPoint(0, 0.5));
                m_progressBar->setPositionX(10 * scale);
                m_percentageLabel->setPositionX(0);
                m_fields->percentageXPos = 0;
            }
        }
        else
        {
            auto ht=Mod::get()->getSettingValue<std::string>("Height");

            if(ht=="Bottom")
            {
                m_progressBar->setPositionY(15);
                m_percentageLabel->setPositionY(15);
            }
            if(pos=="Right")
            {
                m_progressBar->setAnchorPoint(CCPoint(1,0.5f));
                m_progressBar->setPositionX(winSize.width-(50)*scale);
                m_percentageLabel->setAnchorPoint(CCPoint(0,0.5f));
                m_percentageLabel->setPositionX(winSize.width-45*scale);
                m_fields->percentageXPos=winSize.width-45*scale;
            }
            else if(pos=="Left")
            {
                m_progressBar->setPositionX(5);
                m_progressBar->setAnchorPoint(CCPoint(0,0.5f));
                m_percentageLabel->setPositionX(220*scale);
                m_fields->percentageXPos=220*scale;
            }
            else if(pbSetting)
            {
                m_percentageLabel->setPositionX(winSize.width/2+109.5*scale);
                m_fields->percentageXPos=winSize.width/2+109.5*scale;
            }
        }
    };
};