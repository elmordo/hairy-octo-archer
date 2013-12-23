/*
 * Mesh.hpp
 *
 *  Created on: 13.9.2013
 *      Author: petr
 */

#ifndef MESH_HPP_
#define MESH_HPP_

#include <cstddef>

#include "VertexGroup.hpp"

namespace Gremlin {
namespace Mesh {

using namespace std;

typedef std::list<VertexGroup> VGList;

class Mesh : public Gremlin::Graphics::GraphicData {

	/**
	 * seznam skupin vertexu
	 */
	VGList vg;

public:

	/**
	 * vytvori prazdny mesh objekt
	 */
	Mesh();

	/**
	 * kopytor
	 */
	Mesh(const Mesh &o);

	/**
	 * destruktor
	 */
	virtual ~Mesh();

	/**
	 * prida skupinu vertexu a vraci jeji index v seznamu
	 */
	size_t addVGroup();

	/**
	 * vraci pocet materialu pouzitych v objektu
	 */
	virtual size_t materialCount() const;

	/**
	 * vraci pocen skupin vertexu
	 */
	size_t VGCount();

	/**
	 * vraci (konstantni) referenci na skupinu vertexu
	 */
	VertexGroup &VGroup(size_t index);
	const VertexGroup &VGroup(size_t index) const;

	/**
	 * odebere skupinu vertexu
	 */
	void removeVGroup(size_t index);

	/**
	 * vykresli objekt
	 */
	virtual void render(const MaterialMap &mats) const;
};

} /* namespace Mesh */
} /* namespace Gremlin */
#endif /* MESH_HPP_ */
