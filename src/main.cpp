#include <Geode/modify/PlayLayer.hpp>
#include <Geode/loader/Mod.hpp>
using namespace geode::prelude;


class $modify(PlayLayer) {
    struct Fields {
        bool progressBarFound = false;
        int frameFound=0;
        int percentageXPos=394.5;
        CCPoint anchor=CCPoint(0,0.5f);
    };
    static void onModify(auto& self) {
        self.setHookPriorityPost("PlayLayer::init", Priority::VeryLate);
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        if(m_progressBar&&m_percentageLabel&&!m_fields->progressBarFound)
        {
            moveProgressBar();
            m_fields->progressBarFound=true;
        }
        else
        {
            m_fields->frameFound++;
        
        }
        return true;
    };

    void updateProgressbar()
    {
        PlayLayer::updateProgressbar();
        if(m_progressBar&&m_percentageLabel&&!m_fields->progressBarFound)
        {
            moveProgressBar();
            m_fields->progressBarFound=true;
        }
        else
        {
            m_fields->frameFound++;
        
        }
        m_percentageLabel->setPositionX(m_fields->percentageXPos);
        m_percentageLabel->setAnchorPoint(m_fields->anchor);
    };
    void moveProgressBar()
    {
        auto winSize = CCDirector::get()->getWinSize();
        
        auto vert=Mod::get()->getSettingValue<bool>("vertical-progress-bar");
        auto pos=Mod::get()->getSettingValue<std::string>("Position");
        auto scale=Mod::get()->getSettingValue<float>("Scale");
        geode::log::info(fmt::runtime("{}"),pos);
        m_progressBar->setScale(scale);
        m_percentageLabel->setScale(scale*0.5);    
            if(vert)
            {
                m_progressBar->setRotation(-90);
                m_progressBar-> setPositionY(winSize.height/2);
                m_percentageLabel->setPositionY(winSize.height/2+120*scale);
                
                
                /*
                CCNode* players = m_progressBar->getChildByType(1);
                bool rotate=false;  
                if (players) {
                    geode::log::info("Globed players detected");
                    rotate=true;
                }
                else
                {
                    geode::log::info("Globed players not detected");
                }
                geode::log::info(fmt::runtime("{}"), rotate);
                */
                if(pos=="Right")
                {
                    m_percentageLabel->setAnchorPoint(CCPoint(1,0.5));
                    m_fields->anchor=CCPoint(1,0.5);
                    m_percentageLabel->setPositionX(winSize.width);
                    m_fields->percentageXPos=winSize.width;
                    m_progressBar-> setPositionX(winSize.width-10*scale);


                }
                else
                {
                    m_progressBar-> setPositionX(10*scale);
                    m_percentageLabel->setPositionX(0);
                    m_fields->percentageXPos=0.5;
                    /*
                    if(rotate)
                    {
                        CCArray* playerList=players->getChildren();
                        for(int i=0;i<playerList->count();i++)
                        {
                            auto player=static_cast<CCNode*>(playerList->objectAtIndex(i));
                            auto simplePlayer=static_cast<CCNode*>(player->getChildren()->objectAtIndex(1));
                            simplePlayer->setRotation(90);
                        }
                    }
                        */
                }
            }
            else
            {
                auto ht=Mod::get()->getSettingValue<std::string>("Heigth");
                geode::log::info(fmt::runtime("{}"), ht);
                if(ht=="Bottom")
                {
                    m_progressBar->setPositionY(15);
                    m_percentageLabel->setPositionY(15);
                }
                if(pos=="Right")
                {
                    m_progressBar->setAnchorPoint(CCPoint(1,0.5f));
                    m_progressBar->setPositionX(winSize.width-(50)*scale);
                    m_fields->anchor= CCPoint(0,0.5f);
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
                else
                {
                    m_percentageLabel->setPositionX(winSize.width/2+109.5*scale);
                    m_fields->percentageXPos=winSize.width/2+109.5*scale;
                }
        }
    };
};

