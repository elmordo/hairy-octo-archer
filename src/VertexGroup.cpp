/*
 * Mesh.cpp
 *
 *  Created on: 21.8.2013
 *      Author: petr
 */

#include "VertexGroup.hpp"

namespace Gremlin {
namespace Mesh {

const size_t VertexGroup::POINT_SIZE = 3;
const size_t VertexGroup::TRIANGLE_SIZE = 3;
const size_t VertexGroup::NORMAL_SIZE = 3;

VertexGroup::VertexGroup() {
}

VertexGroup::VertexGroup(const VertexGroup &o) : GraphicData(o) {
	pl = o.pl;
	tl = o.tl;
	nl = o.nl;
}

VertexGroup::~VertexGroup() {
	// TODO Auto-generated destructor stub
}

int VertexGroup::addPoint(const Math::Point3Df &p, const Math::GLVector &n) {
	// volatni druhe funkce
	return addPoint(p.x(), p.y(), p.z(), n[0], n[1], n[2]);
}

int VertexGroup::addPoint(GLfloat x, GLfloat y, GLfloat z, GLfloat nx, GLfloat ny, GLfloat nz) {
	// zjisteni indexu bodu (bude z neho vypocitan index bodu)
	size_t n = pl.size();

	// zapis bodu do seznamu
	pl.push_back(x);
	pl.push_back(y);
	pl.push_back(z);

	nl.push_back(nx);
	nl.push_back(ny);
	nl.push_back(nz);

	return n / POINT_SIZE;
}

int VertexGroup::addTriangle(size_t p1, size_t p2, size_t p3) {
	// zjisteni velikosti
	size_t size = tl.size();

	// zapis dat trojuhelniku
	tl.push_back(p1);
	tl.push_back(p2);
	tl.push_back(p3);

	// prepocet na index
	return size / TRIANGLE_SIZE;
}

Math::GLVector VertexGroup::normal(size_t index) {
	// navratova hodnota
	Math::GLVector retVal(3);

	// vypocet startovani pozice
	size_t startPos = index * NORMAL_SIZE;

	// zapis dat
	retVal[0] = nl[startPos];
	retVal[1] = nl[startPos + 1];
	retVal[2] = nl[startPos + 2];

	return retVal;
}

void VertexGroup::normal(size_t index, GLfloat x, GLfloat y, GLfloat z) {
	// vypocet startovni pozice
	size_t startPos = index * NORMAL_SIZE;

	nl[startPos] = x;
	nl[startPos + 1] = y;
	nl[startPos + 2] = z;
}

void VertexGroup::normal(size_t index, Math::GLVector n) {
	normal(index, n[0], n[1], n[2]);
}

void VertexGroup::render(const MaterialMap &mats) const {
	// nastaveni materialu
	const MaterialBase *mat = getMaterial(0);

	// kontrola prepisu materialu
	MaterialMap::const_iterator mapPos = mats.find(0);

	if (mapPos != mats.end() && mapPos->second) {
		mat = mapPos->second;
	}

	// pokud je material nastaven, aktivuje se
	if (mat) {
		mat->setup();
	}

	// zapnuti cerpani dat z klientside
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// nastaveni pointeru
	glVertexPointer(3, GL_FLOAT, 0, pl.rawData());
	glNormalPointer(GL_FLOAT, 0, nl.rawData());

	glDrawElements(GL_TRIANGLES, tl.size(), GL_UNSIGNED_INT, tl.rawData());

	// odpojeni klientside
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

VertexGroup &VertexGroup::operator =(const VertexGroup &o) {
	pl = o.pl;
	tl = o.tl;
	nl = o.nl;

	return *this;
}

} /* namespace Graphics */
} /* namespace Gremlin */
