/*
 * Mesh.hpp
 *
 *  Created on: 21.8.2013
 *      Author: petr
 */

#ifndef VERTEXGROUP_HPP_
#define VERTEXGROUP_HPP_

#include <GL/gl.h>
#include <GraphicData.hpp>
#include <Vector.hpp>
#include <vector>
#include <Point3D.hpp>
#include <Vector.hpp>
#include <DirectVector.hpp>
#include <MaterialBase.hpp>
#include <iostream>

using namespace Gremlin::Materials;

namespace Gremlin {
namespace Mesh {

using namespace std;

class VertexGroup : public Graphics::GraphicData {

	const static size_t POINT_SIZE;
	const static size_t TRIANGLE_SIZE;
	const static size_t NORMAL_SIZE;

	/**
	 * seznam bodu
	 * kazdy bod zabira 3 polozky (slozka X, Y a Z)
	 */
	Utils::DirectVector<GLfloat> pl;

	/**
	 * seznam trojuhelniku
	 * kazdy face zabira 3 polozky (indexy 3 bodu v poli bodu pl)
	 */
	Utils::DirectVector<GLuint> tl;

	/**
	 * seznam normal
	 * normala kazdeho face zabira 3 polozky
	 */
	Utils::DirectVector<GLfloat> nl;

public:

	/**
	 * vytvori prazdny mesh
	 */
	VertexGroup();

	/**
	 * prekopiruje mesh
	 */
	VertexGroup(const VertexGroup &o);

	/**
	 * dealokuje data
	 */
	virtual ~VertexGroup();

	/**
	 * prida jeden bod
	 */
	int addPoint(const Math::Point3Df &p, const Math::GLVector &n);
	int addPoint(GLfloat x, GLfloat y, GLfloat z, GLfloat nx, GLfloat ny, GLfloat nz);

	/**
	 * prida trojuhelnik
	 * navratova hodnota je index trojuhelniku / normaly
	 */
	int addTriangle(size_t p1, size_t p2, size_t p3);

	/**
	 * vraci normalnu daneho bodu
	 */
	Math::GLVector normal(size_t index);

	/**
	 * nastavi novou normalu daneho bodu
	 */
	void normal(size_t index, GLfloat x, GLfloat y, GLfloat z);
	void normal(size_t index, Math::GLVector n);

	/**
	 * vraci seznam normal
	 */
	inline const Utils::DirectVector<GLfloat> &normals() const {
		return nl;
	}

	/**
	 * vraci seznam bodu skupiny
	 */
	inline const Utils::DirectVector<GLfloat> &points() const {
		return pl;
	}

	/**
	 * vykresli objekt
	 */
	virtual void render(const MaterialMap &mats) const;

	/**
	 * vraci pocet pouzitych materialu
	 */
	inline size_t materialCount() const {
		return 1;
	}

	/**
	 * vraci seznam trojuhelniku
	 */
	inline const Utils::DirectVector<GLuint> &triangles() const {
		return tl;
	}

	/**
	 * operator prirazeni
	 */
	VertexGroup &operator =(const VertexGroup &o);
};

} /* namespace Graphics */
} /* namespace Gremlin */
#endif /* MESH_HPP_ */
