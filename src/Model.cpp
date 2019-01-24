/**
*  @Model类的实现
*  主要功能为parse 模型obj和纹理png文件，将数据保存至基于QT的数据结构中
*  
*/

#include "Model.h"

Model::Model(QString filename)
{
	
	int c = 0;

	fileName = filename;
	QString textureName;
	QVector3D temp3D;
	QVector2D temp2D;
	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		//int i = 1;
		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QTextStream fileText(&file);
			while (!fileText.atEnd())
			{
				QString fileLine = fileText.readLine();
				//stream << endl<< "Line:"<< fileLine << endl;
				if (fileLine.startsWith("usemtl "))
				{
					continue;
				}
				/*针对obj格式含vn的情况，保留以供未来拓展。
				else if (fileLine.startsWith("vn "))
				{
					//stream << " 8vn";
					QStringList lineList = fileLine.split(" ");
					temp3D.setX(lineList[1].toFloat());
					temp3D.setY(lineList[2].toFloat());
					temp3D.setZ(lineList[3].toFloat());
					/VNormals.push_back(temp3D);
				}
				*/
				else if (fileLine.startsWith("v "))
				{ 
					QStringList lineList = fileLine.split(" ");
					temp3D.setX(lineList[1].toFloat());
					temp3D.setY(lineList[2].toFloat());
					temp3D.setZ(lineList[3].toFloat());
					Vertices.push_back(temp3D);
				}
				else if (fileLine.startsWith("vt "))
				{
					QStringList lineList = fileLine.split(" ");
					temp2D.setX(lineList[1].toFloat());
					temp2D.setY(lineList[2].toFloat());
					UVs.push_back(temp2D);
				}
				
				else if (fileLine.startsWith("f "))
				{
					Face face;
					QStringList lineList = fileLine.split(" ");

					for (int i = 1; i <= 3; i++)
					{

						QStringList arg = lineList[i].split("/");
						// eos导出的obj格式不含vn。当然，为了兼容所有其他obj，该语句保留
						//face.vn[i - 1] = VNormals[arg[2].toInt() - 1];
						face.v[i - 1] = Vertices[arg[0].toInt() - 1];
						face.t[i - 1] = UVs[arg[1].toInt() - 1];
						
					}
					Faces.push_back(face);
				}
				else if (fileLine.startsWith("mtllib "))
				{
					QStringList lineList = fileLine.split(" ");
					textureName = lineList[1];
				}
				if (fileText.atEnd())
				{
					break;
				}
			}

		}

		QFileInfo fi(fileName);
		QString BaseName = fi.fileName();
		QString fn(fileName);
		fn.remove(fn.size() - BaseName.size(), BaseName.size());
		LoadMTL(fn, fn + textureName);

	}
}

void Model::render()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < Faces.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//glNormal3f(Faces[i].vn[j].x(), Faces[i].vn[j].y(), Faces[i].vn[j].z());
			glTexCoord2f(Faces[i].t[j].x(), Faces[i].t[j].y());
			glVertex3f(Faces[i].v[j].x(), Faces[i].v[j].y(), Faces[i].v[j].z());
		}
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}

void Model::LoadMTL(QString fn, QString MTLname)
{
	if (!MTLname.isEmpty())
	{
		QFile file(MTLname);

		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QTextStream fileText(&file);
			while (!fileText.atEnd())
			{
				QString fileLine = fileText.readLine();
				if (fileLine.startsWith("map_Kd "))
				{
					QStringList lineList = fileLine.split(" ");
					textureName = fn + lineList[1];
					LoadTexture();
				}
			}
		}
		file.close();
	}
}

void Model::LoadTexture()
{
	textureImg = QImage(textureName, "PNG");
	//qDebug() << "image loaded";
	textureImg = QGLWidget::convertToGLFormat(textureImg);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImg.width(), textureImg.height(), 0, GL_RGBA,
		GL_UNSIGNED_BYTE, textureImg.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}

