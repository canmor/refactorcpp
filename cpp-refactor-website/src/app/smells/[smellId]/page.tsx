import fs from 'fs';
import path from 'path';
import { notFound } from 'next/navigation';
import { Card, CardHeader, CardTitle, CardDescription, CardContent } from '@/components/ui/card';
import { Badge } from '@/components/ui/badge';
import { getHighlighter, bundledLanguages } from 'shiki'; // Or import from prism-react-renderer

// Define the structure of a code smell based on your data.json
interface CodeExample {
  title: string;
  codePath: string; // Relative to content root e.g. smells/long-method/before.cpp
  explanation: string;
  code?: string; // To be populated with actual code content
}

interface RefactoringTechnique {
  name: string;
  description: string;
}

interface CodeSmellData {
  id: string;
  name: string;
  description: string;
  cppExamples: CodeExample[];
  refactoringTechniques: RefactoringTechnique[];
  relatedSmells?: string[];
}

// Function to get all smell IDs for generateStaticParams
export async function generateStaticParams() {
  const smellsDirectory = path.join(process.cwd(), 'src', 'content', 'smells');
  const smellFolders = fs.readdirSync(smellsDirectory, { withFileTypes: true })
    .filter(dirent => dirent.isDirectory())
    .map(dirent => dirent.name);
  return smellFolders.map(id => ({ smellId: id }));
}

async function getSmellData(smellId: string): Promise<CodeSmellData | null> {
  const smellDataPath = path.join(process.cwd(), 'src', 'content', 'smells', smellId, 'data.json');
  if (!fs.existsSync(smellDataPath)) {
    return null;
  }
  const fileContents = fs.readFileSync(smellDataPath, 'utf8');
  const data = JSON.parse(fileContents) as CodeSmellData;

  // Initialize shiki highlighter
  const highlighter = await getHighlighter({
    themes: ['github-dark'], // Or your preferred theme
    langs: ['cpp', 'c', 'json', 'bash'] // Include languages you need
  });

  // Load code for examples
  for (const example of data.cppExamples) {
    const codeFilePath = path.join(process.cwd(), 'src', 'content', example.codePath);
    if (fs.existsSync(codeFilePath)) {
      const rawCode = fs.readFileSync(codeFilePath, 'utf8');
      example.code = highlighter.codeToHtml(rawCode, { lang: 'cpp', theme: 'github-dark' });
    } else {
      example.code = '<p>Code file not found.</p>';
    }
  }
  return { ...data, id: smellId };
}

export default async function SmellDetailPage({ params }: { params: { smellId: string } }) {
  const smell = await getSmellData(params.smellId);

  if (!smell) {
    notFound();
    return; // Ensure notFound stops execution or returns a value
  }

  return (
    <div className="container mx-auto p-4">
      <article>
        <header className="mb-8">
          <h1 className="text-4xl font-bold mb-2">{smell.name}</h1>
          <p className="text-lg text-muted-foreground">{smell.description}</p>
        </header>

        {smell.cppExamples && smell.cppExamples.length > 0 && (
          <section className="mb-8">
            <h2 className="text-2xl font-semibold mb-4">C++ Examples</h2>
            {smell.cppExamples.map((example, index) => (
              <Card key={index} className="mb-6">
                <CardHeader>
                  <CardTitle>{example.title}</CardTitle>
                </CardHeader>
                <CardContent>
                  {example.explanation && <p className="mb-4 text-sm text-muted-foreground">{example.explanation}</p>}
                  {/* Ensure shiki HTML is rendered correctly */}
                  {example.code && <div dangerouslySetInnerHTML={{ __html: example.code }} className="bg-background rounded-md p-4 overflow-x-auto" />}
                </CardContent>
              </Card>
            ))}
          </section>
        )}

        {smell.refactoringTechniques && smell.refactoringTechniques.length > 0 && (
          <section className="mb-8">
            <h2 className="text-2xl font-semibold mb-4">Refactoring Techniques</h2>
            <div className="space-y-4">
              {smell.refactoringTechniques.map((technique, index) => (
                <Card key={index}>
                  <CardHeader>
                    <CardTitle>{technique.name}</CardTitle>
                  </CardHeader>
                  <CardContent>
                    <p>{technique.description}</p>
                  </CardContent>
                </Card>
              ))}
            </div>
          </section>
        )}

        {smell.relatedSmells && smell.relatedSmells.length > 0 && (
          <section>
            <h2 className="text-2xl font-semibold mb-4">Related Smells</h2>
            <div className="flex flex-wrap gap-2">
              {smell.relatedSmells.map((relatedId) => (
                <Badge key={relatedId} variant="secondary">
                  {/* Ideally, these would be links if you have a way to map IDs to names/links */}
                  {relatedId}
                </Badge>
              ))}
            </div>
          </section>
        )}
      </article>
    </div>
  );
}
