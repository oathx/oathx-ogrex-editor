USE [master]
GO
/****** 对象:  Database [QPGameMatchDB]    脚本日期: 12/08/2008 11:50:05 ******/
CREATE DATABASE [QPGameMatchDB] ON  PRIMARY 
( NAME = N'QPGameMatchDB', FILENAME = N'D:\数据库\QPGameMatchDB.mdf' , SIZE = 3328KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'QPGameMatchDB_log', FILENAME = N'D:\数据库\QPGameMatchDB_log.LDF' , SIZE = 6272KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
 COLLATE Chinese_PRC_CI_AS
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [QPGameMatchDB].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [QPGameMatchDB] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [QPGameMatchDB] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [QPGameMatchDB] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [QPGameMatchDB] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [QPGameMatchDB] SET ARITHABORT OFF 
GO
ALTER DATABASE [QPGameMatchDB] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [QPGameMatchDB] SET AUTO_CREATE_STATISTICS ON 
GO
ALTER DATABASE [QPGameMatchDB] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [QPGameMatchDB] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [QPGameMatchDB] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [QPGameMatchDB] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [QPGameMatchDB] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [QPGameMatchDB] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [QPGameMatchDB] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [QPGameMatchDB] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [QPGameMatchDB] SET  READ_WRITE 
GO
ALTER DATABASE [QPGameMatchDB] SET RECOVERY FULL 
GO
ALTER DATABASE [QPGameMatchDB] SET  MULTI_USER 
GO
if ( ((@@microsoftversion / power(2, 24) = 8) and (@@microsoftversion & 0xffff >= 760)) or 
		(@@microsoftversion / power(2, 24) >= 9) )begin 
	exec dbo.sp_dboption @dbname =  N'QPGameMatchDB', @optname = 'db chaining', @optvalue = 'OFF'
 end