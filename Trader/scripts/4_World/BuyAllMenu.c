static int TraderUUID = -1;
static int ItemID = -1;
static string ItemName = "";
class BuyAllMenu extends UIScriptedMenu
{
    ButtonWidget m_BtnBuyAllConfirm;
    ButtonWidget  m_BtnClose;
    EditBoxWidget m_ItemValueBox;
    bool m_active = false;

    void BuyAllMenu()
    {

    }
    void ~BuyAllMenu()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        player.GetInputController().SetDisabled(false);
    }
    override Widget Init()
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets( "TM/Trader/scripts/layouts/TraderBuyAll.layout" );

        m_BtnBuyAllConfirm = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btn_confirmBuyAll"));
        m_BtnClose = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btn_closeBuyAll"));
        m_ItemValueBox = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ItemQuantBox"));

        m_active = true;

        return layoutRoot;

    }
    override void OnShow()
    {
        super.OnShow();

        PPEffects.SetBlurMenu(0.5);

        SetFocus(layoutRoot);

        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);

        GetGame().GetUIManager().ShowUICursor( true );

    }
    override void OnHide()
	{
		super.OnHide();

        PPEffects.SetBlurMenu(0);

        GetGame().GetInput().ResetGameFocus();

        GetGame().GetMission().PlayerControlEnable(false);

        GetGame().GetUIManager().ShowUICursor( false );

        Close();
    }

    override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if(w == m_BtnBuyAllConfirm)
        {  
            //string m_input = m_ItemValueBox.GetText();
            HandleSendRPC();
            GetGame().GetUIManager().Back();
            return true;
        }
        if(w == m_BtnClose)
        {
            GetGame().GetUIManager().Back();

			return true;
        }
        return false;
    }
    bool isDigisOnly(string input)
    {
        /*switch(input)
        {
            case "1":
                return true;
                break;
            case "2":
                return true;
                break;
            case "3":
                return true;
                break;
            case "4":
                return true;
                break;
            case "5":
                return true;
                break;
            case "6":
                return true;
                break;
            case "7":
                return true;
                break;
            case "8":
                return true;
                break;
            case "9":
                return true;
                break;
        }
        return false;
        */
        
    }

    void HandleSendRPC()
    {
        if(TraderUUID != -1 && ItemID != -1 && m_ItemValueBox.GetText().ToInt() != 0 && ItemName != "")
        {
            PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
            GetGame().RPCSingleParam(player, TRPCs.RPC_BUYALL, new Param4<int, int, int, string>( TraderUUID, ItemID, m_ItemValueBox.GetText().ToInt(), ItemName), true);
        }
    }
}