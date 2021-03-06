/**
* @file include/ctypes/annotation_out.h
* @brief A representation of @c out annotation.
* @copyright (c) 2017 Avast Software, licensed under the MIT license
*/

#ifndef CTYPES_ANNOTATION_OUT_H
#define CTYPES_ANNOTATION_OUT_H

#include "ctypes/annotation.h"

namespace ctypes {

/**
* @brief A representation of @c out annotation.
*/
class AnnotationOut: public Annotation
{
	public:
		AnnotationOut(const std::string &name): Annotation(name) {};
		static std::shared_ptr<AnnotationOut> create(
			const std::shared_ptr<Context> &context,
			const std::string &name);

		virtual bool isOut() const override;
};

} // namespace ctypes

#endif
