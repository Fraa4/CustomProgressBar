#include <Geode/modify/PlayLayer.hpp>
#include <Geode/loader/Mod.hpp>
using namespace geode::prelude;


class $modify(PlayLayer) {
    struct Fields {
        bool progressBarFound = false;
        int frameFound=0;
        int percentageXPos=394.5;
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
    };
    void moveProgressBar()
    {
        auto vert=Mod::get()->getSettingValue<bool>("vertical-progress-bar");
        auto pos=Mod::get()->getSettingValue<std::string>("Position");
            geode::log::info(fmt::runtime("{}"),pos);
            
            if(vert)
            {
                m_progressBar->setRotation(-90);
                m_progressBar-> setPositionY(160);
                m_percentageLabel->setPositionY(280);
                
                CCNode* players = m_progressBar->getChildByType(1);
                /*
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
                    m_percentageLabel->setPositionX(564);
                    m_fields->percentageXPos=564;
                    m_progressBar-> setPositionX(559);


                }
                else
                {
                    m_progressBar-> setPositionX(10);
                    m_percentageLabel->setPositionX(0.5);
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
                    m_progressBar->setPositionX(425.5);
                    m_percentageLabel->setPositionX(535.5);
                    m_fields->percentageXPos=535.5;
                }
                else if(pos=="Left")
                {
                    m_progressBar->setPositionX(114.5);
                    m_percentageLabel->setPositionX(224.5);
                    m_fields->percentageXPos=224.5;
                }
        }
    };
};

