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
  object Splitter2: TSplitter
    Left = 0
    Top = 0
    Width = 3
    Height = 538
    Cursor = crHSplit
  end
  object Splitter1: TSplitter
    Left = 476
    Top = 0
    Width = 7
    Height = 538
    Cursor = crHSplit
    Align = alRight
  end
  object Panel2: TPanel
    Left = 483
    Top = 0
    Width = 248
    Height = 538
    Align = alRight
    Caption = 'Panel2'
    TabOrder = 0
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
  object PageControl1: TPageControl
    Left = 3
    Top = 0
    Width = 473
    Height = 538
    ActivePage = TabSheet1
    Align = alClient
    TabIndex = 0
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = #1054#1094#1077#1085#1086#1095#1085#1099#1081' '#1072#1083#1075#1086#1088#1080#1090#1084
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 465
        Height = 510
        Align = alClient
        Caption = 'Panel1'
        TabOrder = 0
        object Chart1: TChart
          Left = 1
          Top = 1
          Width = 463
          Height = 508
          BackWall.Brush.Color = clWhite
          BackWall.Brush.Style = bsClear
          MarginBottom = 0
          MarginLeft = 0
          MarginRight = 0
          MarginTop = 0
          Title.Text.Strings = (
            'TChart')
          Title.Visible = False
          OnScroll = Chart1Scroll
          OnZoom = Chart1Zoom
          BottomAxis.ExactDateTime = False
          BottomAxis.LabelStyle = talValue
          BottomAxis.TickLength = 5
          DepthAxis.LabelsFont.Charset = DEFAULT_CHARSET
          DepthAxis.LabelsFont.Color = clBlack
          DepthAxis.LabelsFont.Height = -12
          DepthAxis.LabelsFont.Name = 'Arial'
          DepthAxis.LabelsFont.Style = []
          Legend.Alignment = laTop
          Legend.ColorWidth = 100
          Legend.ShadowSize = 1
          Legend.TopPos = 0
          View3D = False
          Align = alClient
          Color = clWhite
          TabOrder = 0
          object Series1: TLineSeries
            Marks.ArrowLength = 8
            Marks.Visible = False
            SeriesColor = clRed
            Title = 'SIGNAL'
            LinePen.Style = psDash
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
            LinePen.Style = psDot
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
            LinePen.Style = psDashDot
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
          object Series4: TPointSeries
            Marks.ArrowLength = 0
            Marks.Visible = False
            SeriesColor = clYellow
            Pointer.Brush.Color = clLime
            Pointer.InflateMargins = True
            Pointer.Style = psTriangle
            Pointer.Visible = True
            XValues.DateTime = False
            XValues.Name = 'X'
            XValues.Multiplier = 1
            XValues.Order = loAscending
            YValues.DateTime = False
            YValues.Name = 'Y'
            YValues.Multiplier = 1
            YValues.Order = loNone
          end
          object Series5: TPointSeries
            Marks.ArrowLength = 0
            Marks.Visible = False
            SeriesColor = clBlue
            Pointer.InflateMargins = True
            Pointer.Style = psTriangle
            Pointer.Visible = True
            XValues.DateTime = False
            XValues.Name = 'X'
            XValues.Multiplier = 1
            XValues.Order = loAscending
            YValues.DateTime = False
            YValues.Name = 'Y'
            YValues.Multiplier = 1
            YValues.Order = loNone
          end
          object Series7: TPointSeries
            Marks.ArrowLength = 0
            Marks.Visible = False
            SeriesColor = clGray
            Pointer.Brush.Color = clRed
            Pointer.InflateMargins = True
            Pointer.Style = psTriangle
            Pointer.Visible = True
            XValues.DateTime = False
            XValues.Name = 'X'
            XValues.Multiplier = 1
            XValues.Order = loAscending
            YValues.DateTime = False
            YValues.Name = 'Y'
            YValues.Multiplier = 1
            YValues.Order = loNone
          end
          object Series8: TPointSeries
            Marks.ArrowLength = 40
            Marks.Font.Charset = DEFAULT_CHARSET
            Marks.Font.Color = clBlack
            Marks.Font.Height = -15
            Marks.Font.Name = 'Arial'
            Marks.Font.Style = [fsBold]
            Marks.Transparent = True
            Marks.Visible = True
            SeriesColor = clFuchsia
            Pointer.Brush.Color = clRed
            Pointer.InflateMargins = True
            Pointer.Style = psDownTriangle
            Pointer.Visible = True
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
    end
    object TabSheet2: TTabSheet
      Caption = #1057#1080#1084#1091#1083#1103#1090#1086#1088' '#1072#1083#1075#1086#1088#1080#1090#1084#1072
      ImageIndex = 1
      object Panel4: TPanel
        Left = 0
        Top = 0
        Width = 465
        Height = 510
        Align = alClient
        Caption = 'Panel4'
        TabOrder = 0
        object Chart2: TChart
          Left = 1
          Top = 1
          Width = 463
          Height = 508
          BackWall.Brush.Color = clWhite
          BackWall.Brush.Style = bsClear
          Title.Text.Strings = (
            'TChart')
          Title.Visible = False
          OnScroll = Chart2Scroll
          OnZoom = Chart2Zoom
          Legend.Alignment = laTop
          Legend.LegendStyle = lsSeries
          Legend.TextStyle = ltsPlain
          View3D = False
          Align = alClient
          TabOrder = 0
          object Series6: TLineSeries
            Marks.ArrowLength = 8
            Marks.Visible = False
            SeriesColor = clRed
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
    end
  end
end
