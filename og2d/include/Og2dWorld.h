#ifndef _____Og2dWorld_H
#define _____Og2dWorld_H

#include "Og2dSingleton.h"
#include "Og2dScene.h"
#include "Og2dViewport.h"

namespace Og2d
{
	enum WorldMask{
		WORLD_PAGE_SECNE
	};
	
	// 场景映射表
	typedef HashMap<String, Scene*>		SceneMapTab;
	// 视口映射表
	typedef HashMap<String, Viewport*>	ViewportTab;
	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-08-03
	*
	* \Author  : lp
	*
	* \Desc    : 世界对象
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API World : public Singleton<World>
	{
	public:
		/** 实现获取单件引用
		 *
		 * \return 
		 */
		static	World&				getSingleton();

		/** 使用获取单件指针
		 *
		 * \return 
		 */
		static	World*				getSingletonPtr();
	public:
		/**
		 *
		 * \param vOrigin 
		 * \param cSize 
		 * \return 
		 */
		World(const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual ~World();

		/**
		 *
		 * \param szName 
		 */
		virtual	void			setName(const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual	String			getName() const;

		/**
		 *
		 * \param vPos 
		 * \param cSize 
		 * \return 
		 */
		virtual	Viewport*		createViewport(const String& name, const Vector2D& vPos);
		
		/**
		 *
		 * \param name 
		 */
		virtual	void			destroyViewport(const String& name);

		/**
		 *
		 * \return 
		 */
		virtual Viewport*		getViewport() const;

		/**
		 *
		 * \param pViewport 
		 */
		virtual	void			destroyAllViewprot();

		/** 创建创建
		 *
		 * \param szCreateFactoryName 
		 * \param szName 
		 * \return 
		 */
		virtual	Scene*			createScene(const String& szCreateFactoryName, const String& szName,
			const Vector2D& vPos, const Size& cSize);
		
		/** 获取场景
		 *
		 * \param szName 
		 * \return 
		 */
		virtual	Scene*			getScene(const String& szName);
		
		/** 销毁指定场景
		 *
		 * \param pScene 
		 */
		virtual	void			destroyScene(Scene* pScene);

		/** 销毁指定场景
		 *
		 * \param szName 
		 */
		virtual	void			destroyScene(const String& szName);

		/** 销毁所有场景对象
		 *
		 */
		virtual	void			destroyAllScene();

		/** 设置当前需要更新的场景
		 *
		 * \param pScene 
		 */
		virtual	void			setNeedUpdateScene(Scene* pScene);

		/** 返回当前正在更新的场景
		 *
		 * \return 
		 */
		virtual	Scene*			getNeedUpdateScene() const;

		/** 周期性更新，只更新需要更新的场景对象
		 *
		 * \param fElapsed 
		 */
		virtual	void			update(float fElapsed);
		
	protected:
		// 世界名
		String					m_szName;
		// 场景映射表
		SceneMapTab				m_MapSceneTab;
		// 当前需要更新的场景
		Scene*					m_pNeedUpdateScene;
		// 当前视口
		Viewport*				m_pViewport;
		// 视口表
		ViewportTab				m_MapViewport;

	};
}

#endif