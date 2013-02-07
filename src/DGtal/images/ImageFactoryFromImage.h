/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file ImageFactoryFromImage.h
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/01/23
 *
 * Header file for module ImageFactoryFromImage.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImageFactoryFromImage_RECURSES)
#error Recursive header files inclusion detected in ImageFactoryFromImage.h
#else // defined(ImageFactoryFromImage_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImageFactoryFromImage_RECURSES

#if !defined ImageFactoryFromImage_h
/** Prevents repeated inclusion of headers. */
#define ImageFactoryFromImage_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/images/CImage.h"
#include "DGtal/base/Alias.h"
#include "DGtal/images/ImageAdapter.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // Template class ImageFactoryFromImage
  /**
   * Description of template class 'ImageFactoryFromImage' <p>
   * \brief Aim: todo
   */
  template <typename TImageContainer>
  class ImageFactoryFromImage
  {

    // ----------------------- Types ------------------------------

  public:
    typedef ImageFactoryFromImage<TImageContainer> Self; 
    
    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( CImage<TImageContainer> ));

    ///Types copied from the container
    typedef TImageContainer ImageContainer;
    typedef typename TImageContainer::Domain Domain;
    typedef typename TImageContainer::Value Value;
    
    ///New types
    typedef ImageAdapter<TImageContainer, Domain, DefaultFunctor, Value, DefaultFunctor, DefaultFunctor > AdaptedImage;
    typedef ImageContainerBySTLVector<Domain, Value> OutputImage;
    //typedef ImageAdapter<TImageContainer, Domain, DefaultFunctor, Value, DefaultFunctor, DefaultFunctor > OutputImage;

    // ----------------------- Standard services ------------------------------

  public:

    ImageFactoryFromImage(Alias<ImageContainer> anImage):
      myImagePtr(anImage)
    {
    }

    /**
     * Destructor.
     * Does nothing
     */
    ~ImageFactoryFromImage() {}

    // ----------------------- Interface --------------------------------------
  public:

    /////////////////// Domains //////////////////


    /////////////////// Accessors //////////////////

    
    /////////////////// API //////////////////

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    /**
     * @return the validity of the Image
     */
    bool isValid() const
    {
      return (myImagePtr->isValid());
    }

    /**
     * Returns a pointer of an OutputImage created with the Domain aDomain.
     * @return an ImagePtr.
     */
    OutputImage * request(const Domain &aDomain)
    {
      DefaultFunctor idD;
      DefaultFunctor idV;
      DefaultFunctor idVm1;
        
      AdaptedImage* adaptImage = new AdaptedImage(*myImagePtr, aDomain, idD, idV, idVm1);
      typename AdaptedImage::Range rout = adaptImage->range(); 
      
      OutputImage* outputImage = new OutputImage(aDomain);
      typename OutputImage::Range rin = outputImage->range();
      
      std::copy(rout.begin(), rout.end(), rin.begin());
      
      delete adaptImage;
      
      //OutputImage* outputImage = new OutputImage(*myImagePtr, aDomain, idD, idV, idVm1);
        
      return outputImage;
    }
    
    /**
     * Flush an OutputImage
     */
    void flushImage(OutputImage* outputImage)
    {
      typename OutputImage::Range rout = outputImage->range();
      typename ImageContainer::Range rin = myImagePtr->range();
      
      std::copy(rout.begin(), rout.end(), rin.begin()); // temp
    }
    
    /**
     * Free an OutputImage
     */
    void detachImage(OutputImage* outputImage)
    {
      delete outputImage;
    }

    // ------------------------- Protected Datas ------------------------------
  private:
    /**
     * Default constructor.
     */
    ImageFactoryFromImage() {}
    
    // ------------------------- Private Datas --------------------------------
  protected:

    /// Alias on the image container
    ImageContainer * myImagePtr;

  private:


    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class ImageFactoryFromImage


  /**
   * Overloads 'operator<<' for displaying objects of class 'ImageFactoryFromImage'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ImageFactoryFromImage' to write.
   * @return the output stream after the writing.
   */
  template <typename TImageContainer>
  std::ostream&
  operator<< ( std::ostream & out, const ImageFactoryFromImage<TImageContainer> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/images/ImageFactoryFromImage.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImageFactoryFromImage_h

#undef ImageFactoryFromImage_RECURSES
#endif // else defined(ImageFactoryFromImage_RECURSES)
