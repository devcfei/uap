#ifndef _APP_H_
#define _APP_H_


using namespace uap;

class App : public LogTraceHelper
{
public:
    App();
    ~App();


    Result createApplication();
    Result initApplication();

    Result startUI();
    Result setLayout();



private:

    sptr<IApplication> spApp_;
    sptr<IToml> spToml_;    
    Result initApplicationConfiguration();


    sptr<IUiEngine> spUiEngine_;
    sptr<IAttributes> spUiAttributes_;

    Result initUiEngine();



    sptr<IUiLayout> spLayout_;
    sptr<IAttributes> spLayoutAttributes_;


    std::string strAppPath_;
    Result buildLayout();
    Result buildMenuBar();
    Result buildToolBar();
    Result buildStatusBar();    
    Result buildImageWindow();
    Result buildTextureInspector();

};




#endif //@_APP_H_