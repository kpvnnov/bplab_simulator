object Form1: TForm1
  Left = 222
  Top = 147
  Width = 739
  Height = 565
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 483
    Height = 538
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 0
    object Chart1: TChart
      Left = 1
      Top = 1
      Width = 481
      Height = 536
      BackWall.Brush.Color = clWhite
      BackWall.Brush.Style = bsClear
      Title.Text.Strings = (
        'TChart')
      OnScroll = Chart1Scroll
      OnZoom = Chart1Zoom
      View3D = False
      Align = alClient
      TabOrder = 0
      object Series1: TLineSeries
        Marks.ArrowLength = 8
        Marks.Visible = False
        SeriesColor = clRed
        Title = 'SIGNAL'
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        Pointer.Visible = False
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Multiplier = 1
        XValues.Order = loAscending
        YValues.DateTime = False
        YValues.Name = 'Y'
        YValues.Multiplier = 1
        YValues.Order = loNone
      end
      object Series2: TLineSeries
        Marks.ArrowLength = 8
        Marks.Visible = False
        SeriesColor = clGreen
        Title = 'DIFF'
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        Pointer.Visible = False
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Multiplier = 1
        XValues.Order = loAscending
        YValues.DateTime = False
        YValues.Name = 'Y'
        YValues.Multiplier = 1
        YValues.Order = loNone
      end
      object Series3: TLineSeries
        Marks.ArrowLength = 8
        Marks.Visible = False
        SeriesColor = 16744448
        Title = 'DIFF2'
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        Pointer.Visible = False
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Multiplier = 1
        XValues.Order = loAscending
        YValues.DateTime = False
        YValues.Name = 'Y'
        YValues.Multiplier = 1
        YValues.Order = loNone
      end
    end
  end
  object Panel2: TPanel
    Left = 483
    Top = 0
    Width = 248
    Height = 538
    Align = alRight
    Caption = 'Panel2'
    TabOrder = 1
    object FilterComboBox1: TFilterComboBox
      Left = 16
      Top = 264
      Width = 145
      Height = 21
      FileList = FileListBox1
      Filter = 'CSV files (*.cvs)|*.csv|All files (*.*)|*.*'
      TabOrder = 1
    end
    object Edit1: TEdit
      Left = 16
      Top = 8
      Width = 121
      Height = 21
      TabOrder = 2
      Text = '*.csv'
    end
    object FileListBox1: TFileListBox
      Left = 16
      Top = 48
      Width = 145
      Height = 201
      FileEdit = Edit1
      ItemHeight = 13
      Mask = '*.csv'
      TabOrder = 3
      OnClick = FileListBox1Click
    end
    object Panel3: TPanel
      Left = 1
      Top = 352
      Width = 246
      Height = 185
      Align = alBottom
      Caption = 'Panel3'
      TabOrder = 0
      DesignSize = (
        246
        185)
      object DriveComboBox1: TDriveComboBox
        Left = 48
        Top = 142
        Width = 145
        Height = 19
        DirList = DirectoryListBox1
        TabOrder = 0
      end
      object DirectoryListBox1: TDirectoryListBox
        Left = 5
        Top = 16
        Width = 233
        Height = 97
        Anchors = [akRight, akBottom]
        FileList = FileListBox1
        ItemHeight = 16
        TabOrder = 1
      end
    end
  end
end
