#include <Geode/modify/PlayLayer.hpp>
#include <Geode/loader/Mod.hpp>
using namespace geode::prelude;


class $modify(PlayLayer) {
    struct Fields {
        //Calls two times since after the first time it is called playlayer moves the percentageXPosition after updateProgressBar
        int moveProgressBar = 2;
        bool pbSetting=false, pgSetting=false;
        int frameFound = 0;
        int test=1;
    };
    
    void updateProgressbar()
    {
        //Check if progressBar and percentageLabel settings are changed and save new values

        bool pbNewSetting = GameManager::get()->m_showProgressBar;
        bool pbChanged = (pbNewSetting != m_fields->pbSetting);
        bool pgNewSetting = GameManager::get()->getGameVariable("0040");
        bool pgChanged = (pgNewSetting != m_fields->pgSetting);
        m_fields->pbSetting=pbNewSetting;
        m_fields->pgSetting=pgNewSetting;
        
        PlayLayer::updateProgressbar();
        float opacity=Mod::get()->getSettingValue<float>("Opacity")*255;
        m_progressBar->setOpacity(opacity);
        CCSprite* image=m_progressBar->getChildByType<CCSprite>(0);
        image->setOpacity(opacity);
        m_percentageLabel->setOpacity(opacity);
        if(!m_isPlatformer)
        {

            //run the function if any settings has changed
            bool runFunc=pbChanged || pgChanged;

            if(m_fields->moveProgressBar>0 || runFunc)
            {
                moveProgressBarNoPlat();
                log::info("classic level");
                m_fields->moveProgressBar--;
                log::debug("moved progress bar");
                if(runFunc)
                {
                    log::info("Settings modified");
                }
            }
        }
    };
    // for some reason this function resets the x position each frame so the function to initialize y position and anchor are run only the first time and
    // the function to set x position is run each frame
    void updateTimeLabel(int p0, int p1, bool p2)
    {
        PlayLayer::updateTimeLabel(p0,p1,p2);
        
        if(m_isPlatformer)
        {
            if(m_fields->moveProgressBar>0)
            {
                log::info("platformer level");
                moveProgressBarPlatInitialize();
                m_fields->moveProgressBar--;
            }
            moveProgressBarPlatSetX();
        }
    }
    
    void moveProgressBarNoPlat()
    {
        auto winSize = CCDirector::get()->getWinSize();
        
        auto vert = Mod::get()->getSettingValue<bool>("vertical-progress-bar");
        auto pos = Mod::get()->getSettingValue<std::string>("Position");
        auto scale = Mod::get()->getSettingValue<float>("Scale");
        auto offset = Mod::get()->getSettingValue<int>("Border-offset");
        bool pbSetting=m_fields->pbSetting;

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
                m_percentageLabel->setPositionX(winSize.width-offset*scale);
                m_progressBar->setPositionX(winSize.width+(-10-offset) * scale);
            }
            else
            {
                m_percentageLabel->setAnchorPoint(CCPoint(0, 0.5));
                m_progressBar->setPositionX((10+offset) * scale);
                m_percentageLabel->setPositionX(offset*scale);
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
                m_progressBar->setPositionX(winSize.width-(50+offset)*scale);
                m_percentageLabel->setAnchorPoint(CCPoint(0,0.5f));
                m_percentageLabel->setPositionX(winSize.width-(45+offset)*scale);
            }
            else if(pos=="Left")
            {
                m_progressBar->setPositionX(offset);
                m_progressBar->setAnchorPoint(CCPoint(0,0.5f));
                m_percentageLabel->setAnchorPoint(CCPoint(0,0.5f));
                if(pbSetting)
                {
                    m_percentageLabel->setPositionX(5+offset+215*scale);
                }
                else
                {
                    m_percentageLabel->setPositionX(10+offset);
                }
            }
            else if(pbSetting)
            {
                m_percentageLabel->setPositionX(winSize.width/2+109.5*scale);
            }
        }
    };
    void moveProgressBarPlatInitialize()
    {
        auto winSize = CCDirector::get()->getWinSize();
        auto scale = Mod::get()->getSettingValue<float>("Scale");
        auto ht=Mod::get()->getSettingValue<std::string>("Height");
        m_percentageLabel->setScale(scale*0.5);

        if(ht=="Bottom")
        {
            m_percentageLabel->setPositionY(15);
        }

    };
    void moveProgressBarPlatSetX()
    {
        auto winSize = CCDirector::get()->getWinSize();
        auto pos = Mod::get()->getSettingValue<std::string>("Position");
        
        auto offset = Mod::get()->getSettingValue<int>("Border-offset");
        if(pos=="Right")
        {
            m_percentageLabel->setAnchorPoint(CCPoint(1,0.5f));
            m_percentageLabel->setPositionX(winSize.width-offset);
        }
        else if(pos=="Left")
        {
            m_percentageLabel->setAnchorPoint(CCPoint(0,0.5f));
            m_percentageLabel->setPositionX(offset);
        }
    }
};