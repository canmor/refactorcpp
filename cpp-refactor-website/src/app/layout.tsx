import type { Metadata } from "next";
import { Inter } from "next/font/google";
import "./globals.css";
import Header from "@/components/layout/Header"; // Import the new header
import { ThemeProvider } from "@/components/theme-provider"; // Assuming you might have this from shadcn

const inter = Inter({ subsets: ["latin"] });

export const metadata: Metadata = {
  title: "C++ RefactorHub - Learn C++ Refactoring",
  description: "Interactive guide to C++ code smells, refactoring techniques, and quizzes.",
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en" suppressHydrationWarning>
      <body className={inter.className}>
        <ThemeProvider
          attribute="class"
          defaultTheme="system"
          enableSystem
          disableTransitionOnChange
        >
          <Header />
          <main className="container mx-auto p-4 mt-6"> {/* Add some margin-top for content */}
            {children}
          </main>
        </ThemeProvider>
      </body>
    </html>
  );
}
