#include "TitleScene.h"
#include"Engine/Camera.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "resource.h"
#include "UDPServer.h"

HINSTANCE hInst;

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1)
{
}

//������
void TitleScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("matchingStay.jpg");
	assert(hPict_ >= 0);
}

//�X�V
void TitleScene::Update()
{
	if (UDPServer::GetIsStart())
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//�`��
void TitleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void TitleScene::Release()
{
}


BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int  nCmdShow)
{
    hInst = hInstance;
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
    return (int)0;
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    HWND hMessageEdit = GetDlgItem(hDlg, IDD_DIALOG1);
    switch (msg) {
    case IDC_IPADDRESS1:
       /* switch (LOWORD(wp)) {
        case IDC_SENDBUTTON:
            message += L"aaa\r\n";
            SetWindowText(hMessageEdit, message.c_str());
            return TRUE;
        case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
            return TRUE;
        }*/
        return FALSE;
    case IDC_EDIT1:
        return TRUE;
    }

    return FALSE;
}
//
////�_�C�A���O
//BOOL TitleScene::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
//{
//    switch (msg)
//    {
//    case IDC_IPADDRESS1:
//        //SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);
//
//        //SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)"1-�f�t�H���g");//�_�C�A���O�����\��
//        //SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)"2-�����K");
//        //SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)"3-��");
//        //SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)"4-��");
//        //SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)"5-��");
//
//        //SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_SETCURSEL, 0, 0);//�ŏ��ɕ\�����镶��
//
//        return TRUE;
//    case IDC_EDIT1:
//       /* switch (LOWORD(wp))
//        {
//        case IDC_RADIO_UP:
//            mode_ = 0;
//            return TRUE;
//        case IDC_RADIO_DOWN:
//            mode_ = 1;
//            return TRUE;
//        case IDC_RADIO_CHANGE:
//            mode_ = 2;
//            return TRUE;
//        case IDC_COMBO_TYPE:
//            select_ = (int)SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_GETCURSEL, 0, 0);
//            return TRUE;
//        default:
//            break;
//        }*/
//        return TRUE;
//    }
//    return FALSE;
//}