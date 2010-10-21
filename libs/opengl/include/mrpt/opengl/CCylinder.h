/* +---------------------------------------------------------------------------+
   |          The Mobile Robot Programming Toolkit (MRPT) C++ library          |
   |                                                                           |
   |                   http://mrpt.sourceforge.net/                            |
   |                                                                           |
   |   Copyright (C) 2005-2010  University of Malaga                           |
   |                                                                           |
   |    This software was written by the Machine Perception and Intelligent    |
   |      Robotics Lab, University of Malaga (Spain).                          |
   |    Contact: Jose-Luis Blanco  <jlblanco@ctima.uma.es>                     |
   |                                                                           |
   |  This file is part of the MRPT project.                                   |
   |                                                                           |
   |     MRPT is free software: you can redistribute it and/or modify          |
   |     it under the terms of the GNU General Public License as published by  |
   |     the Free Software Foundation, either version 3 of the License, or     |
   |     (at your option) any later version.                                   |
   |                                                                           |
   |   MRPT is distributed in the hope that it will be useful,                 |
   |     but WITHOUT ANY WARRANTY; without even the implied warranty of        |
   |     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
   |     GNU General Public License for more details.                          |
   |                                                                           |
   |     You should have received a copy of the GNU General Public License     |
   |     along with MRPT.  If not, see <http://www.gnu.org/licenses/>.         |
   |                                                                           |
   +---------------------------------------------------------------------------+ */
#ifndef opengl_CCylinder_H
#define opengl_CCylinder_H

#include <mrpt/opengl/CRenderizable.h>

namespace mrpt	{
namespace opengl	{
	class OPENGL_IMPEXP CCylinder;
	// This must be added to any CSerializable derived class:
	DEFINE_SERIALIZABLE_PRE_CUSTOM_BASE_LINKAGE(CCylinder,CRenderizable, OPENGL_IMPEXP)
	/** A cylinder or cone whose base lies in the XY plane.
	  * \sa opengl::COpenGLScene,opengl::CDisk
	  *  
	  *  <div align="center">
	  *  <table border="0" cellspan="4" cellspacing="4" style="border-width: 1px; border-style: solid;">
	  *   <tr> <td> mrpt::opengl::CCylinder </td> <td> \image html preview_CCylinder.png </td> </tr>
	  *  </table>
	  *  </div>
	  *  
	  */
	class OPENGL_IMPEXP CCylinder:public CRenderizable	{
		DEFINE_SERIALIZABLE(CCylinder)
	protected:
		/**
		  * Cylinder's radii. If mBaseRadius==mTopRadius, then the object is an actual cylinder. If both differ, it's a truncated cone. If one of the radii is zero, the object is a cone.
		  */
		float mBaseRadius,mTopRadius;
		/**
		  * Cylinder's height
		  */
		float mHeight;
		/**
		  * Implementation parameters on which depend the number of actually rendered polygons.
		  */
		uint32_t mSlices,mStacks;
		/**
		  * Boolean parameters about including the bases in the object. If both mHasTopBase and mHasBottomBase are set to false, only the lateral area is displayed.
		  */
		bool mHasTopBase,mHasBottomBase;
	public:
		/**
		  * Constructor with two radii. Allows the construction of any cylinder.
		  */
		static CCylinderPtr Create(const float baseRadius,const float topRadius,const float height=1,const int slices=10,const int stacks=10)	{
			return CCylinderPtr(new CCylinder(baseRadius,topRadius,height,slices,stacks));
		}
		/** Render
		  * \sa mrpt::opengl::CRenderizable
		  */
		void render() const;
		/**
		  * Ray tracing.
		  * \sa mrpt::opengl::CRenderizable
		  */
		virtual bool traceRay(const mrpt::poses::CPose3D &o,double &dist) const;
		/**
		  * Configuration of the cylinder's bases display.
		  */
		inline void setHasBases(bool top=true,bool bottom=true)	{
			mHasTopBase=top;
			mHasBottomBase=bottom;
		}
		/**
		  * Check whether top base is displayed.
		  * \sa hasBottomBase
		  */
		inline bool hasTopBase() const	{
			return mHasTopBase;
		}
		/**
		  * Check whether bottom base is displayed.
		  * \sa hasTopBase
		  */
		inline bool hasBottomBase() const	{
			return mHasBottomBase;
		}
		/**
		  * Sets both radii to a single value, thus configuring the object as a cylinder.
		  * \sa setRadii
		  */
		inline void setRadius(float radius)	{
			mBaseRadius=mTopRadius=radius;
		}
		/**
		  * Sets both radii independently.
		  * \sa setRadius
		  */
		inline void setRadii(float bottom,float top)	{
			mBaseRadius=bottom;
			mTopRadius=top;
		}
		/**
		  * Chenges cylinder's height.
		  */
		inline void setHeight(float height)	{
			mHeight=height;
		}
		/**
		  * Gets the bottom radius.
		  */
		inline float getBottomRadius() const	{
			return mBaseRadius;
		}
		/**
		  * Gets the top radius.
		  */
		inline float getTopRadius() const	{
			return mTopRadius;
		}
		/**
		  * Gets the cylinder's height.
		  */
		inline float getHeight() const	{
			return mHeight;
		}
		/**
		  * Gets how many slices are used in the cylinder's lateral area and in its bases.
		  */
		inline void setSlicesCount(uint32_t slices)	{
			mSlices=slices;
		}
		/**
		  * Gets how many stacks are used in the cylinder's lateral area.
		  */
		inline void setStacksCount(uint32_t stacks)	{
			mStacks=stacks;
		}
		/**
		  * Sets the amount of slices used to display the object.
		  */
		inline uint32_t getSlicesCount() const	{
			return mSlices;
		}
		/**
		  * Sets the amount of stacks used to display the object.
		  */
		inline uint32_t getStacksCount() const	{
			return mStacks;
		}
	private:
		/**
		  * Basic empty constructor. Set all parameters to default.
		  */
		CCylinder():mBaseRadius(1),mTopRadius(1),mHeight(1),mSlices(10),mStacks(10),mHasTopBase(true),mHasBottomBase(true)	{};
		/**
		  * Complete constructor. Allows the configuration of every parameter.
		  */
		CCylinder(const float baseRadius,const float topRadius,const float height,const int slices,const int stacks):mBaseRadius(baseRadius),mTopRadius(topRadius),mHeight(height),mSlices(slices),mStacks(stacks),mHasTopBase(true),mHasBottomBase(true)	{};
		/**
		  * Destructor.
		  */
		virtual ~CCylinder() {};
		/**
		  * Gets the radius of the circunference located at certain height, returning false if the cylinder doesn't get that high.
		  */
		inline bool getRadius(float Z,float &r) const	{
			if (!reachesHeight(Z)) return false;
			r=(Z/mHeight)*(mTopRadius-mBaseRadius)+mBaseRadius;
			return true;
		}
		/**
		  * Checks whether the cylinder exists at some height.
		  */
		inline bool reachesHeight(float Z) const	{
			return (mHeight<0)?(Z>=mHeight&&Z<=0):(Z<=mHeight&&Z>=0);
		}
	};
}
}
#endif
