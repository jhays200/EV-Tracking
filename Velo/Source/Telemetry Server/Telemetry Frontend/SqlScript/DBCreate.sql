USE [TricsWeb]

/****** Object:  Table [dbo].[Sensors]    Script Date: 05/02/2010 10:11:45 ******/
SET ANSI_NULLS ON

SET QUOTED_IDENTIFIER ON

SET ANSI_PADDING ON

CREATE TABLE [dbo].[Sensors](
	[sensorName] [varchar](256) NOT NULL,
	[deviceName] [varchar](256) NOT NULL,
	[displayName] [varchar](64) NOT NULL,
	[valueCount] [int] NULL,
	[errorCount] [int] NULL,
	[descript] [varchar](2056) NULL,
	[minValue] [int] NULL,
	[maxValue] [int] NULL,
	[valueName] [varchar](2056) NULL,
 CONSTRAINT [PK_Sensors] PRIMARY KEY CLUSTERED 
(
	[sensorName] ASC,
	[deviceName] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

SET ANSI_PADDING OFF

/****** Object:  Table [dbo].[SensorData]    Script Date: 05/02/2010 10:11:45 ******/
SET ANSI_NULLS ON

SET QUOTED_IDENTIFIER ON

SET ANSI_PADDING ON

CREATE TABLE [dbo].[SensorData](
	[deviceName] [varchar](256) NOT NULL,
	[sensorName] [varchar](256) NOT NULL,
	[dateReceived] [datetime] NOT NULL,
	[data] [varchar](2056) NULL,
	[error] [bit] NULL,
 CONSTRAINT [PK_SensorData_1] PRIMARY KEY CLUSTERED 
(
	[deviceName] ASC,
	[sensorName] ASC,
	[dateReceived] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

SET ANSI_PADDING OFF

/****** Object:  Table [dbo].[Display]    Script Date: 05/02/2010 10:11:45 ******/
SET ANSI_NULLS ON

SET QUOTED_IDENTIFIER ON

SET ANSI_PADDING ON

CREATE TABLE [dbo].[Display](
	[displayName] [varchar](64) NULL,
	[displayDefinition] [xml] NULL,
	[displayType] [varchar](64) NULL
) ON [PRIMARY]

SET ANSI_PADDING OFF

/****** Object:  Table [dbo].[Devices]    Script Date: 05/02/2010 10:11:45 ******/
SET ANSI_NULLS ON

SET QUOTED_IDENTIFIER ON

SET ANSI_PADDING ON

CREATE TABLE [dbo].[Devices](
	[deviceName] [varchar](256) NOT NULL,
	[dateRegistered] [datetime] NOT NULL,
	[passkey] [varchar](16) NULL,
	[descript] [varchar](2056) NULL,
 CONSTRAINT [PK_Devices] PRIMARY KEY CLUSTERED 
(
	[deviceName] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

SET ANSI_PADDING OFF

/****** Object:  Table [dbo].[DeviceMarks]    Script Date: 05/02/2010 10:11:45 ******/
SET ANSI_NULLS ON

SET QUOTED_IDENTIFIER ON

SET ANSI_PADDING ON

CREATE TABLE [dbo].[DeviceMarks](
	[deviceName] [varchar](256) NOT NULL,
	[markStart] [datetime] NOT NULL,
	[markEnd] [datetime] NULL,
 CONSTRAINT [PK_DeviceMarks] PRIMARY KEY CLUSTERED 
(
	[deviceName] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

SET ANSI_PADDING OFF

