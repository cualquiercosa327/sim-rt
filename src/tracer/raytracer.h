#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <chrono>
#include <string>

#include "itracer.h"
#include "io/image.h"
#include "io/console.h"
#include "material/imaterial.h"
#include "util/string.h"

namespace rt {
	class Raytracer : public ITracer {
	public:
		Raytracer(size_t width, size_t height, size_t samples, size_t maxdepth = 50);
		Raytracer(Resolution r = Resolution::MEDIUM, Samples s = Samples::MEDIUM, TraceDepth t = TraceDepth::MEDIUM);

		void setHitable(std::shared_ptr<IHitable> h)  override { m_world = h; }
		void setCamera(std::shared_ptr <ICamera> cam) override { m_camera = cam; }
		void setBackgroundColor(vec3 color) override { m_backgroundcolor = color; }
	
		double aspect() const override { return static_cast<double>(m_width) / static_cast<double>(m_height); }

		void run() override;
		void write(std::string filepath) const override;

	private:
		Image                     m_image;
		std::shared_ptr<ICamera>  m_camera;
		std::shared_ptr<IHitable> m_world;
		size_t                    m_width, m_height, m_samples, m_maxdepth;
		vec3                      m_backgroundcolor;

		vec3 trace(const ray& r, int depth) const;
	};
}

#endif//RAYTRACER_H