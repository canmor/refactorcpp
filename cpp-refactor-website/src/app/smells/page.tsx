import fs from 'fs';
import path from 'path';
import Link from 'next/link';
import { Card, CardHeader, CardTitle, CardDescription, CardContent } from '@/components/ui/card'; // Adjust if CardContent is not needed

interface CodeSmell {
  id: string;
  name: string;
  description: string;
  // Add other fields if you plan to display them on the listing page
}

async function getCodeSmells(): Promise<CodeSmell[]> {
  const smellsDirectory = path.join(process.cwd(), 'src', 'content', 'smells');
  const smellFolders = fs.readdirSync(smellsDirectory, { withFileTypes: true })
    .filter(dirent => dirent.isDirectory())
    .map(dirent => dirent.name);

  const smellsData = smellFolders.map(folder => {
    const filePath = path.join(smellsDirectory, folder, 'data.json');
    const fileContents = fs.readFileSync(filePath, 'utf8');
    const data = JSON.parse(fileContents);
    return { ...data, id: folder } as CodeSmell;
  });

  return smellsData;
}

export default async function SmellsPage() {
  const smells = await getCodeSmells();

  return (
    <div className="container mx-auto p-4">
      <h1 className="text-3xl font-bold mb-6">Available Code Smells</h1>
      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-4">
        {smells.map((smell) => (
          <Link href={`/smells/${smell.id}`} key={smell.id} passHref>
            <Card className="hover:shadow-lg transition-shadow">
              <CardHeader>
                <CardTitle>{smell.name}</CardTitle>
                <CardDescription>{smell.description}</CardDescription>
              </CardHeader>
            </Card>
          </Link>
        ))}
      </div>
    </div>
  );
}
