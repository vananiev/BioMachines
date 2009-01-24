object F: TF
  Left = 314
  Top = 101
  AutoScroll = False
  Caption = 'dth'
  ClientHeight = 444
  ClientWidth = 950
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  Scaled = False
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnKeyUp = FormKeyUp
  OnMouseMove = FormMouseMove
  OnMouseWheel = FormMouseWheel
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Shape: TShape
    Left = -1000
    Top = 48
    Width = 17
    Height = 17
    Brush.Color = 16711936
    OnMouseUp = ShapeMouseUp
  end
  object SBar: TStatusBar
    Left = 0
    Top = 424
    Width = 950
    Height = 20
    Panels = <
      item
        Width = 400
      end
      item
        Width = 100
      end
      item
        Width = 50
      end
      item
        Width = 50
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object Inf: TRichEdit
    Left = 776
    Top = 0
    Width = 177
    Height = 425
    Lines.Strings = (
      'Inf')
    TabOrder = 1
    Visible = False
  end
  object pAll: TPanel
    Left = 8
    Top = 320
    Width = 100
    Height = 100
    BorderStyle = bsSingle
    TabOrder = 2
    Visible = False
    object pScr: TPanel
      Left = 16
      Top = 16
      Width = 25
      Height = 25
      Color = clLime
      TabOrder = 0
    end
  end
  object Timer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = TimerTimer
    Left = 216
    Top = 16
  end
  object MainMenu: TMainMenu
    Left = 8
    Top = 16
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
      object N7: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        OnClick = N7Click
      end
      object N8: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        OnClick = N8Click
      end
    end
    object N2: TMenuItem
      Caption = #1057#1086#1089#1090#1086#1103#1085#1080#1077' '#1089#1088#1077#1076#1099
      object N4: TMenuItem
        Caption = #1042#1099#1073#1086#1088' '#1087#1072#1088#1072#1084#1077#1090#1088#1072' '#1089#1086#1089#1090#1086#1103#1085#1080#1103' '#1089#1088#1077#1076#1099
        OnClick = N4Click
      end
      object N9: TMenuItem
        Caption = #1054#1090#1086#1073#1088#1072#1079#1080#1090#1100' '#1089#1086#1089#1090#1086#1103#1085#1080#1103' '#1084#1080#1082#1088#1086#1073#1086#1074' '#1087#1086' '#1088#1072#1079#1076#1088#1072#1078#1080#1090#1077#1083#1102
        OnClick = N9Click
      end
      object N10: TMenuItem
        Caption = #1042#1099#1073#1086#1088' '#1087#1072#1088#1072#1084#1077#1090#1088#1072' '#1088#1072#1079#1076#1088#1072#1078#1080#1090#1077#1083#1103
        OnClick = N10Click
      end
      object N5: TMenuItem
        Caption = #1054#1090#1086#1073#1088#1072#1078#1072#1090#1100' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1102' '#1084#1080#1082#1088#1086#1073#1072
        OnClick = N5Click
      end
      object N6: TMenuItem
        Caption = #1055#1077#1088#1077#1080#1076#1090#1080
        OnClick = N6Click
      end
    end
  end
  object tmrInf: TTimer
    Enabled = False
    Interval = 500
    OnTimer = tmrInfTimer
    Left = 744
  end
  object tmrSlide: TTimer
    Enabled = False
    Interval = 1500
    OnTimer = tmrSlideTimer
    Left = 104
    Top = 328
  end
end
