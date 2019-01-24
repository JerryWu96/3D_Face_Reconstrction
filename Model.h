#pragma once
#pragma once
#ifndef MODEL_H
#define MODEL_H

//QT_FORWARD_DECLARE_CLASS(QOpenGLFunctions_1_1)

#include <QVector>
#include <QTextStream>
#include <QVector3D>
#include <QVector2D>
#include <QtOpenGL>

struct Face
{
	//QVector<QVector3D> vn;

	QVector<QVector3D> v;
	QVector<QVector2D> t;
	Face() {
		v.resize(3);
		t.resize(3);
		//vn.resize(3);
	}
};

class Model
{
public:
	Model() {}
	explicit Model(QString filename);
	void render();

	int faces() const { return Faces.size(); }
	int points() const { return Vertices.size(); }

private:
	QString fileName;
	QString textureName;
	//QVector<QVector3D> VNormals; //vn

	QVector<QVector3D> Vertices; //v
	QVector<QVector2D> UVs;      //vt
	QVector<Face>      Faces;    //f

	GLuint texture;
	QImage textureImg;
	void LoadMTL(QString fn, QString MTLname);
	void LoadTexture();
};

#endif